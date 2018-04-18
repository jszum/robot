TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ./include
INCLUDEPATH += ./src

SOURCES += main.c \
    src/robot_map.c

HEADERS += \
    include/robot_map.h
