TEMPLATE = app
QT = gui core
CONFIG += qt debug warn_on console
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
HEADERS = src/diskreader.h \
 src/common.h \
 src/mftfinder.h \
 src/mftrecord.h \
 src/ntfsbootrecord.h
SOURCES = src/main.cpp \
 src/diskreader.cpp \
 src/mftfinder.cpp \
 src/mftrecord.cpp \
 src/common.cpp \
 src/ntfsbootrecord.cpp
