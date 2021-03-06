#-------------------------------------------------
#
# Project created by QtCreator 2013-12-29T22:23:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ahp
TEMPLATE = app


SOURCES += main.cpp\
        ahpwindow.cpp \
    oknowynikow.cpp

HEADERS  += ahpwindow.h \
    oknowynikow.h

FORMS    += ahpwindow.ui \
    oknowynikow.ui

OTHER_FILES += \
    ku880.ahp \
    ke770.ahp \
    l7.ahp \
    ke850.ahp \
    nexus5.ahp \
    dane/nexus5.ahp \
    dane/l7.ahp \
    dane/ku880.ahp \
    dane/ke850.ahp \
    dane/ke770.ahp \
    dane/przedmioty
