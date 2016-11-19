TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cryptkey.cpp \
    file.cpp \
    transpositioncipher.cpp \
    abstractcipher.cpp

HEADERS += \
    cryptkey.h \
    file.h \
    transpositioncipher.h \
    abstractcipher.h
