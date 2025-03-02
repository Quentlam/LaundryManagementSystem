#-------------------------------------------------
#
# Project created by QtCreator 2025-01-24T00:40:25
#
#-------------------------------------------------
msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

QT       += core gui
QT       += sql
QT       += printsupport
QT       += serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LaundryManagementSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/zint/backend_qt/backend_qt.pro);


CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dlglogin.cpp \
    pulic.cpp \
    userinfo.cpp \
    dlgaddcustomer.cpp \
    dlgaddclothes.cpp \
    dlgadduser.cpp \
    laundrymanagementlogger.cpp \
    customerinfo.cpp \
    clothesinfo.cpp \
    dlgupadateuser.cpp \
    dlgupdateclothes.cpp \
    dlgupdatecustomer.cpp \
    dlggetclothes.cpp \
    dlggetmoney.cpp \
    swpage00.cpp \
    dlgchosecustomer.cpp \
    dlgadd.cpp \
    stselectclothes00.cpp \
    stselectclothes01.cpp \
    stselectclothes02.cpp \
    stselectclothes03.cpp \
    stselectclothes04.cpp \
    dlgupdateclothesotherattributes.cpp \
    dlgaddclothesotherattributes.cpp \
    stselectclothestypeandprice.cpp \
    ordernumbergenerator.cpp \
    dlgdiscount.cpp \
    orderinfo.cpp \
    dlgcustomerrecharge.cpp \
    dlgmanage.cpp \
    dlgneworder.cpp \
    dlgselectclothesinfo.cpp \
    customercost.cpp \
    dlgsearch.cpp \
    dlgordersearch.cpp \
    dlgorderstatus.cpp \
    dlgcustomercostforhavenotpaid.cpp \
    dlgchoseshelf.cpp \
    dlgshelfsearch.cpp \
    dlgshopdata.cpp \
    shopdata.cpp \
    printer.cpp \
    dlgcustomergetclothes.cpp \
    code128generator.cpp \
    printpreviewwidget.cpp

HEADERS += \
        mainwindow.h \
    dlglogin.h \
    pulic.h \
    userinfo.h \
    dlgadd.h \
    dlgaddcustomer.h \
    dlgaddclothes.h \
    dlgadduser.h \
    laundrymanagementlogger.h \
    customerinfo.h \
    clothesinfo.h \
    dlgupadateuser.h \
    dlgupdateclothes.h \
    dlgupdatecustomer.h \
    dlggetclothes.h \
    dlggetmoney.h \
    swpage00.h \
    dlgchosecustomer.h \
    stselectclothes00.h \
    stselectclothes01.h \
    stselectclothes02.h \
    stselectclothes03.h \
    stselectclothes04.h \
    dlgupdateclothesotherattributes.h \
    dlgaddclothesotherattributes.h \
    stselectclothestypeandprice.h \
    ordernumbergenerator.h \
    dlgdiscount.h \
    orderinfo.h \
    dlgcustomerrecharge.h \
    dlgmanage.h \
    dlgneworder.h \
    dlgselectclothesinfo.h \
    customercost.h \
    dlgsearch.h \
    dlgordersearch.h \
    dlgorderstatus.h \
    dlgcustomercostforhavenotpaid.h \
    dlgchoseshelf.h \
    dlgshelfsearch.h \
    dlgshopdata.h \
    shopdata.h \
    printer.h \
    dlgcustomergetclothes.h \
    code128generator.h \
    printpreviewwidget.h

FORMS += \
        mainwindow.ui \
    dlglogin.ui \
    dlgadd.ui \
    dlgaddcustomer.ui \
    dlgaddclothes.ui \
    dlgadduser.ui \
    dlgupadateuser.ui \
    dlgupdateclothes.ui \
    dlgupdatecustomer.ui \
    dlggetclothes.ui \
    dlggetmoney.ui \
    swpage00.ui \
    dlgchosecustomer.ui \
    stselectclothes00.ui \
    stselectclothes01.ui \
    stselectclothes02.ui \
    stselectclothes03.ui \
    stselectclothes04.ui \
    dlgupdateclothesotherattributes.ui \
    dlgaddclothesotherattributes.ui \
    stselectclothestypeandprice.ui \
    dlgdiscount.ui \
    dlgcustomerrecharge.ui \
    dlgmanage.ui \
    dlgneworder.ui \
    dlgselectclothesinfo.ui \
    dlgsearch.ui \
    dlgordersearch.ui \
    dlgorderstatus.ui \
    dlgcustomercostforhavenotpaid.ui \
    dlgchoseshelf.ui \
    dlgshelfsearch.ui \
    dlgshopdata.ui \
    dlgcustomergetclothes.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    src.qrc

DEFINES += ZINT_VERSION="\\\"2.15.0.9\\\""
DEFINES += ZINT_NO_PNG
DEFINES += ENABLE_ENCODER_GENERIC

win32: LIBS += -L$$PWD/../thirdParty/libs/ -lQZXing3
win32: LIBS += -L$$PWD/../thirdParty/libs/ -lQtZint
win32: LIBS += -L$$PWD/../thirdParty/libs/ -lzint

INCLUDEPATH += $$PWD/../thirdParty/include/QZXing
DEPENDPATH += $$PWD/../thirdParty/include/QZXing

INCLUDEPATH += $$PWD/../thirdParty/include/zint/backend_qt
DEPENDPATH += $$PWD/../thirdParty/include/zint/backend_qt
