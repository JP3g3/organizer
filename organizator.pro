#-------------------------------------------------
#
# Project created by QtCreator 2018-03-15T11:12:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = organizator
TEMPLATE = app


SOURCES += main.cpp\
        kalendarz.cpp \
    spotkanie.cpp \
    zdarzenie.cpp

HEADERS  += kalendarz.h \
    spotkanie.h \
    zdarzenie.h

FORMS    += kalendarz.ui \
    spotkanie.ui
