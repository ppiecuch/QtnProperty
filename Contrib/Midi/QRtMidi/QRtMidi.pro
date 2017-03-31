TARGET   = qrtmidi
TEMPLATE = lib
CONFIG += staticlib

RTMIDI_DIR = RtMidi

INCLUDEPATH = $$RTMIDI_DIR $$PWD

HEADERS += \
    $$RTMIDI_DIR/RtError.h \
    $$RTMIDI_DIR/RtMidi.h \
    QRtMidi.h \
    QRtMidiIn.h \
    QRtMidiOut.h \
    QRtMidiData.h \
    QRtMidiIdent.h \
    QRtMidiTrigger.h

SOURCES += \
    $$RTMIDI_DIR/RtMidi.cpp \
    QRtMidi.cpp \
    QRtMidiIn.cpp \
    QRtMidiOut.cpp \
    QRtMidiData.cpp \
    QRtMidiIdent.cpp \
    QRtMidiTrigger.cpp

include("defaults.pri")

# Options for building RtMidi
win32 {
    DEFINES +=__WINDOWS_MM__
}else:macx {
    DEFINES += __MACOSX_CORE__
}


