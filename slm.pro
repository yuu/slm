TEMPLATE = app
TARGET = slm
INCLUDEPATH += ./inc

CONFIG += c++11

# Input
HEADERS += inc/slm.h
SOURCES += src/main.cpp src/slm.cpp

CONFIG += link_pkgconfig
PKGCONFIG += ilm
