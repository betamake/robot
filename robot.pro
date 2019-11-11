QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#添加网络模块
QT +=network
#添加多媒体模块
QT += multimedia multimediawidgets
#添加资源
#
QT += qml quick  xml
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    billidentify.cpp \
    cameradevice.cpp \
    documentjson.cpp \
    facereg.cpp \
    httprequest.cpp \
    interfaceuser.cpp \
    main.cpp \
    mainwindow.cpp \
    previewfile.cpp \
    qrdecode.cpp \
    turing.cpp \
    windows/billitem.cpp \
    windows/scheduleitem.cpp\
    qaudiolevel.cpp \
    voicecontrol.cpp

HEADERS += \
    billidentify.h \
    cameradevice.h \
    documentjson.h \
    facereg.h \
    httprequest.h \
    interfaceuser.h \
    mainwindow.h \
    previewfile.h \
    qrdecode.h \
    turing.h \
    windows/billitem.h \
    windows/scheduleitem.h\
    qaudiolevel.h \
    voicecontrol.h


FORMS += \
    mainwindow.ui \
    windows/billitem.ui \
    windows/scheduleitem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc \
    qml.qrc
