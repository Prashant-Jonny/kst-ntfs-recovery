TEMPLATE = app
QT = core
CONFIG += qt \
 debug \
 warn_on \
 console \
 qtestlib

DESTDIR = bin

OBJECTS_DIR = build

MOC_DIR = build

UI_DIR = build

HEADERS = src/diskreader.h \
 src/diskreadertest.h \
 src/macroses.h
SOURCES = src/main.cpp src/diskreader.cpp src/diskreadertest.cpp
