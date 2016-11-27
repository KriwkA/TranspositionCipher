#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T13:32:26
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_cryptkeytesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_cryptkeytesttest.cpp \
    ../../src/cryptkey.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/cryptkey.h
