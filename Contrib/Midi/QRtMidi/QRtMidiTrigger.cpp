#include "QRtMidiTrigger.h"
#include <QThread>

//-------------------------------------------------------------------------
QRtMidiTrigger::QRtMidiTrigger( QString pattern )
{
    reset();
    _signal = 0;
    setRegExp(pattern);
}

//-------------------------------------------------------------------------
QRtMidiTrigger::QRtMidiTrigger( QString pattern,const QObject *receiver, const char *member )
{
    reset();
    setRegExp(pattern);
    _signal = new DcSignal(receiver,member,this);

}

//-------------------------------------------------------------------------
QRtMidiTrigger::QRtMidiTrigger( QRtMidiData& pattern )
{
    reset();
    _signal = 0;
    setRegExp(pattern.toString());
}

//-------------------------------------------------------------------------
void QRtMidiTrigger::setRegExp( QString pattern )
{
    pattern = pattern.replace(" ","");
    pattern = pattern.replace("0x","");
    QMutexLocker locker(&_mtx);
    _regex = QRegExp(pattern);
    _queue.clear();
}

//-------------------------------------------------------------------------
bool QRtMidiTrigger::dequeue( QRtMidiData& md )
{
    QMutexLocker locker(&_mtx);
    if(_queue.count() > 0)
    {
        md = _queue.dequeue();
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------
bool QRtMidiTrigger::handler( QRtMidiData& md )
{
    QMutexLocker locker(&_mtx);
    _queue.enqueue(md);
    
    _count++;

    while(1)
    {
        bool bk = _lockMtx.tryLock();
        if(bk)
        {
            _lockMtx.unlock();
            break;
        }
        else
        {
            // Failed to get lock, so this better be true, if it's not, wait until it is.
            while(!_waitting)
            {
                QThread::msleep(1);
            }
        }
    }

    if(_waitting)
    {
        _wc.wakeAll();
        _waitting=false;
        // qDebug() << "QRtTriggerChannel WaitCondition Trigger: " << (quintptr)this << "\n";
    }

    // queue overflow protection
    if(_queue.size() > kMaxQueueSize)
    {
        _queue.removeLast();
        qDebug() << "QRtTriggerChannel Overflow: " << (quintptr)this << "\n";
    }

    if(_signal)
    {
        _signal->invoke();
    }
    return allowFutherProcessing();
}

//-------------------------------------------------------------------------
bool QRtMidiTrigger::wait( unsigned long time /*= ULONG_MAX*/ )
{
    _lockMtx.lock();
    _waitting = true;

    bool rtval = _wc.wait(&_lockMtx,time);
    _lockMtx.unlock();
    
    return rtval;
}

//-------------------------------------------------------------------------
void QRtMidiTrigger::reset()
{
    _count = 0;
    _waitting = false;
    _allowFutherProcessing = true;
}



//-------------------------------------------------------------------------
void DcSignal::invoke()
{
    QMetaObject::invokeMethod(const_cast<QObject *>(_reciver), _methodName.constData(), Qt::QueuedConnection,Q_ARG(void*,_usrParam));
}

//-------------------------------------------------------------------------
DcSignal::DcSignal( const QObject* recv, const char* method, void* user /*= 0*/ )
{
    _methodName = 0;
    _reciver = 0;
    _usrParam = 0;

    // Methods must take param
    const char* bracketPosition = strchr(method, '(');
    if (!bracketPosition || !(method[0] == '1')) 
    {
        qWarning("DcSignal - Invalid member specification");
    }
    else
    {
        QByteArray methodName(method+1, bracketPosition - 1 - method); // extract method name
        _methodName = methodName;
        _reciver    = recv;
        _usrParam = user;
    }

}
