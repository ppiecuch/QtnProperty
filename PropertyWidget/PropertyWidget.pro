include(../Config.pri)

TARGET = QtnPropertyWidget
TEMPLATE = lib
VERSION = 1.1.0

QT += core gui widgets script
CONFIG += staticlib
CONFIG += qtn_unity_build

qtn_unity_build: SOURCES += QtnPropertyWidgetUnity.cpp
else: SOURCES += PropertyWidget.cpp \
    PropertyView.cpp \
    Utils/InplaceEditing.cpp \
    Delegates/PropertyDelegateFactory.cpp \
    Delegates/Core/PropertyDelegateBool.cpp \
    Delegates/Core/PropertyDelegateInt.cpp \
    Delegates/Core/PropertyDelegateUInt.cpp \
    Delegates/Core/PropertyDelegateQString.cpp \
    Delegates/Core/PropertyDelegateFloat.cpp \
    Delegates/Core/PropertyDelegateDouble.cpp \
    Delegates/Core/PropertyDelegateEnum.cpp \
    Delegates/Core/PropertyDelegateQRect.cpp \
    Delegates/Utils/PropertyEditorHandler.cpp \
    Delegates/Core/PropertyDelegateEnumFlags.cpp \
    Delegates/PropertyDelegate.cpp \
    Delegates/PropertyDelegateAux.cpp \
    Delegates/Utils/PropertyDelegatePropertySet.cpp \
    Delegates/Utils/PropertyDelegateSliderBox.cpp \
    Delegates/Utils/PropertyDelegateMisc.cpp \
    Delegates/Utils/PropertyEditorAux.cpp \
    Delegates/Core/PropertyDelegateQSize.cpp \
    Delegates/Core/PropertyDelegateQPoint.cpp \
    Delegates/GUI/PropertyDelegateQFont.cpp \
    Delegates/GUI/PropertyDelegateQColor.cpp \
    Delegates/GUI/PropertyDelegateQPen.cpp \
    Delegates/GUI/PropertyDelegateQBrush.cpp \
    Delegates/GUI/PropertyDelegateButton.cpp \
    Utils/AccessibilityProxy.cpp

HEADERS += PropertyWidgetAPI.h \
    PropertyWidget.h \
    PropertyView.h \
    Utils/InplaceEditing.h \
    Delegates/PropertyDelegate.h \
    Delegates/Utils/PropertyDelegatePropertySet.h \
    Delegates/Utils/PropertyDelegateSliderBox.h \
    Delegates/Utils/PropertyDelegateMisc.h \
    Delegates/PropertyDelegateAux.h \
    Delegates/PropertyDelegateFactory.h \
    Delegates/PropertyDelegateSlideBox.h \
    Delegates/Core/PropertyDelegateBool.h \
    Delegates/Core/PropertyDelegateInt.h \
    Delegates/Core/PropertyDelegateUInt.h \
    Delegates/Core/PropertyDelegateQString.h \
    Delegates/Core/PropertyDelegateFloat.h \
    Delegates/Core/PropertyDelegateDouble.h \
    Delegates/Core/PropertyDelegateEnum.h \
    Delegates/Core/PropertyDelegateQRect.h \
    Delegates/Utils/PropertyEditorHandler.h \
    Delegates/Core/PropertyDelegateEnumFlags.h \
    Delegates/Utils/PropertyEditorAux.h \
    Delegates/Core/PropertyDelegateQSize.h \
    Delegates/Core/PropertyDelegateQPoint.h \
    Delegates/GUI/PropertyDelegateQFont.h \
    Delegates/GUI/PropertyDelegateQPen.h \
    Delegates/GUI/PropertyDelegateQBrush.h \
    Delegates/GUI/PropertyDelegateQColor.h \
    Delegates/GUI/PropertyDelegateButton.h \
    Utils/AccessibilityProxy.h

LIBS += -L$$BIN_DIR -lQtnPropertyCore
INCLUDEPATH += $$TOP_SRC_DIR/Core

exists("$$PWD/../Contrib/Midi") {
	message("Midi connector enabled.")
	include("$$PWD/../Contrib/Midi/qtMidi/qtMidi.pri")
}
