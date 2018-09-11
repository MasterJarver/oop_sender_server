TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    server.cpp \
    getfilesize.cpp

HEADERS += \
    server.h \
    getfilesize.h
