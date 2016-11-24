#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T13:30:20
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = tst_filetesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_filetesttest.cpp \
    ../../src/file.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/file.h
