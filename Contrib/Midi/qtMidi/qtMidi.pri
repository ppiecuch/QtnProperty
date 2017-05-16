QT += gui widgets
INCLUDEPATH += $$PWD/ext

SOURCES += \
    $$PWD/ext/aspectratiopixmaplabel.cpp \
    $$PWD/net/udpmidi.cpp \
    $$PWD/midisetup.cpp

HEADERS += \
    $$PWD/ext/aspectratiopixmaplabel.h \
    $$PWD/net/constants.h \
    $$PWD/net/netsettings.h \
    $$PWD/net/udpmidi.h \
    $$PWD/midisetup.h

FORMS += \
    $$PWD/midisetup.ui

RESOURCES += \
    $$PWD/qtMidi.qrc

include(../QRtMidi/QRtMidi.pri)

