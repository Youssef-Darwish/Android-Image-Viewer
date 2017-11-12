#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T16:24:57
#
#-------------------------------------------------

QT       += core gui androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = androidImageEditor
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qgraphicsviewn.cpp

HEADERS += \
        mainwindow.h \
    qgraphicsviewn.h

FORMS += \
        mainwindow.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    android-sources/AndroidManifest.xml \
    android-sources/src/com/amin/QtAndroidGallery/QtAndroidGallery.java \
    res/default.jpg \
    res/about.png \
    res/background.png \
    res/crop.png \
    res/open.png \
    res/reset.png \
    res/rotate.png \
    res/save.png \
    res/select.png \
    res/zoomIn.png \
    res/zoomOut.png

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

RESOURCES += \
    res/images.qrc

