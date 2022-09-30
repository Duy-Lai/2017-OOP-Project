QT             += opengl
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ex_p10_qt_gl

LIBS += -L../general -lgeneral -lopengl32
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc \
    vue_opengl.cc \
    glsphere.cc

HEADERS += \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    glsphere.h \
    ../general/SupportADessin.h \
    ../general/Dessinable.h \
    ../general/Milieu.h \
    ../general/Grain.h \
    ../general/Obstacle.h \
    ../general/Source.h \
    ../general/Environnement.h \
    ../general/Systeme.h \
    
RESOURCES += \
    resource.qrc
