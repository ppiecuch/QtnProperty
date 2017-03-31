#pragma once

#include <QMutex>
#include <QRegExp>
#include <QString>
#include <QMutexLocker>
#include <QQueue>
#include <QWaitCondition>
#include <QByteArray>

#include "QRtMidiData.h"
#include "QRtMidiIn.h"

class DcSioMidi;

class DcSignal
{
public:

    DcSignal() : _reciver(0) {};
    DcSignal(const QObject* recv, const char* method, void* user = 0);
    void invoke();

private:
    const QObject* _reciver;
    QByteArray _methodName;
    void* _usrParam;

};

// const_cast<QObject *>(


class QRtMidiTrigger
{
    
    static const int kMaxQueueSize = 200;

public:
    
    QRtMidiTrigger() : _waitting(false),_count(0),_allowFutherProcessing(true),_signal(0) {} ;

    QRtMidiTrigger(QString pattern);
    
    QRtMidiTrigger(QRtMidiData& pattern);

    QRtMidiTrigger(QString pattern,const QObject *receiver, const char *member);

    void reset();

    ~QRtMidiTrigger() 
    {
        if(_signal)
            delete _signal;
    }

    inline QRegExp getRegExp() const { return _regex; }
    
    void setRegExp(QRegExp val) { _regex = val; }
    
    void setRegExp(QString pattern);

    bool dequeue(QRtMidiData& md);

    bool allowFutherProcessing() const { return _allowFutherProcessing; }
    
    void setAllowFutherProcessing(bool val) { _allowFutherProcessing = val; }

    bool wait(unsigned long time = ULONG_MAX);

    void lock() {_mtx.lock();}
    
    void unlock() {_mtx.unlock();}

    quint32 getCount() { return _count; }
    quint32 clearCount() { return _count; }

private:
    friend class QRtMidiIn;
    friend class DcSioMidi;

    bool handler(QRtMidiData& md);

    QRegExp               _regex;
    QWaitCondition        _wc;
    
    QQueue<QRtMidiData>  _queue;
    

    QMutex _mtx;
    QMutex _lockMtx;
    bool _waitting;
    int   _count;
    bool _allowFutherProcessing;
    DcSignal* _signal;
};

/*!
    The QRtAutoTrigger is a convenience class that simplifies adding
    and removing "trigger channels" to and from a Midi input object.

    QRtAudoTrigger should be created within a function where a
    temporary QRtTriggerChannel is needed to detect some response
    from a midi device.  Once the QRtAutoTrigger goes out of scope
    it will remove the trigger channel from the QRtMidiIn device.
!*/

class QRtAutoTrigger
{

public:

    inline QRtAutoTrigger(QRtMidiTrigger* tc, QRtMidiIn* dev)
    {
        Q_ASSERT(dev);
        Q_ASSERT(tc);
        _tc = tc;
        _dev = dev;
        dev->addTrigger(*tc);
        deleteTc = false;
    }

    inline QRtAutoTrigger(QString pattern, QRtMidiIn* dev)
    {
        Q_ASSERT(dev);
        _tc = new QRtMidiTrigger(pattern);
        if(_tc)
        {
            deleteTc = true;
            _dev = dev;
            dev->addTrigger(*_tc);
        }
        // TODO: throw on allocation error
    }

    // A method to change the current trigger pattern and reset the
    // trigger internals
    inline void setPattern(QString pattern)
    {
        if(_tc)
        {
            _tc->setRegExp(pattern);
            _tc->reset();
        }
    }

    inline bool dequeue(QRtMidiData& md) {return _tc->dequeue(md);}
    inline bool wait(unsigned int timems) {return _tc->wait(timems);}
    inline quint32 getCount() {return _tc->getCount();}
    inline void clearCount() {_tc->clearCount();}

    inline ~QRtAutoTrigger()
    {
        _dev->removeTrigger(*_tc);

        if(deleteTc && _tc)
        {
            delete _tc;
        }
    };

private:

    QRtMidiIn* _dev;
    QRtMidiTrigger* _tc;
    bool deleteTc;

};

