QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataBase.cpp \
    data.cpp \
    datapacket.cpp \
    drawplot.cpp \
    main.cpp \
    logwidget.cpp \
    mainpageproxy.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    serialport.cpp

HEADERS += \
    DataBase.h \
    data.h \
    datapacket.h \
    drawplot.h \
    logwidget.h \
    mainpageproxy.h \
    mainwindow.h \
    qcustomplot.h \
    serialport.h

FORMS += \
    logwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
