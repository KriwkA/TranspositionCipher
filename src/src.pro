TEMPLATE = app

QT     += core gui widgets
CONFIG += c++11

SOURCES += main.cpp \
    cryptkey.cpp \
    file.cpp \
    transpositioncipher.cpp \
    abstractcipher.cpp \
    mainwindow.cpp \
    cipherdialog.cpp

HEADERS += \
    cryptkey.h \
    file.h \
    transpositioncipher.h \
    abstractcipher.h \
    mainwindow.h \
    cipherdialog.h

FORMS += \
    mainwindow.ui \
    cipherdialog.ui
