TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -ligraph

SOURCES += main.cpp \
    sim.cpp \
    misc.cpp \
    bmlrp.cpp

HEADERS += \
    sim.h \
    bmlrp.h \
    misc.h

OTHER_FILES += \
    export.cpp \
    export.h
