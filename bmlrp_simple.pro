TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -ligraph

SOURCES += main.cpp \
    sim.cpp \
    misc.cpp \
    bmlrp.cpp \
    graph.cpp

HEADERS += \
    sim.h \
    bmlrp.h \
    misc.h \
    graph.h \
    stable.h \
    myassert.h

OTHER_FILES += \
    export.cpp \
    export.h

PRECOMPILED_HEADER += stable.h
