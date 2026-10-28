QT += core gui opengl widgets
contains(QT_VERSION, ^6\\..*) {
    QT += openglwidgets
}
QMAKE_CXXFLAGS += -std=c++17

win32:LIBS += -lopengl32

DEFINES += GL_SILENCE_DEPRECATION
TARGET = main_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general/include

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
    ../general/include/dessinable.h \
    ../general/include/support_a_dessin.h \
    ../general/include/Systeme.h \
    ../general/include/particule.h \
    ../general/include/Vecteur3D.h \
    ../general/include/Enceinte.h \
    ../general/include/SousParticules.h \
    ../general/include/GenerateurAleatoire.h \

RESOURCES += \
    resource.qrc
