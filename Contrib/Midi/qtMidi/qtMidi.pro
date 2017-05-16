TARGET = qtMidiTest
TEMPLATE = app

QT += gui widgets
INCLUDEPATH += ext
CONFIG -= app_bundle

SOURCES += \
    ext/aspectratiopixmaplabel.cpp \
    net/udpmidi.cpp \
    midisetup.cpp \
    mainwindow.cpp \
    main.cpp

HEADERS += \
    ext/aspectratiopixmaplabel.h \
    net/constants.h \
    net/netsettings.h \
    net/udpmidi.h \
    mainwindow.h \
    midisetup.h

FORMS += \
    midisetup.ui

RESOURCES += \
    qtMidiTest.qrc

include(../QRtMidi/QRtMidi.pri)

