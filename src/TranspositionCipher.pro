TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cryptkey.cpp \
    cryptograph.cpp \
    file.cpp

HEADERS += \
    cryptkey.h \
    cryptograph.h \
    file.h
