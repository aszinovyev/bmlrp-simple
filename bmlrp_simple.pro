TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    graph.cpp \
    sim.cpp \
    export.cpp \
    misc.cpp

LIBS += -ligraph

HEADERS += \
    graph.h \
    sim.h \
    bmlrp.h \
    misc.h
