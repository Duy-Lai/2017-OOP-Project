QMAKE_CXXFLAGS += -std=c++11

TARGET = ex_p10_text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_text.cc \
    TextViewer.cc
    
HEADERS += \
    TextViewer.h \
    ../general/SupportADessin.h \
    ../general/Dessinable.h \
    ../general/Milieu.h \
    ../general/Grain.h \
    ../general/Obstacle.h \
    ../general/Source.h \
    ../general/Environnement.h \
    ../general/Systeme.h \
