TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    sim.cpp \
    misc.cpp \
    bmlrp.cpp \
    debug.cpp \
    test.cpp \
    graph.cpp

HEADERS += \
    sim.h \
    bmlrp.h \
    misc.h \
    graph.h \
    debug.h \
    test.h

OTHER_FILES += \
    network_r.h \
    network_r.cpp \
    export.h \
    export.cpp
