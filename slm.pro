TEMPLATE = app
TARGET = slm
INCLUDEPATH += ./inc

CONFIG += c++11

# Input
HEADERS += inc/slm.h
SOURCES += src/main.cpp src/slm.cpp

INCLUDEPATH += ${PKG_CONFIG_SYSROOT_DIR}/usr/include
LIBS += -L${PKG_CONFIG_SYSROOT_DIR} -lilmControl -lilmCommon
