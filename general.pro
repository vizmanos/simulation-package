TEMPLATE = lib

CONFIG = staticlib
QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH = include
INCLUDEPATH = src

SOURCES += \
    src/Systeme.cc \
    src/particule.cc \
    src/SousParticules.cc \
    src/Vecteur3D.cc \
    src/Enceinte.cc

HEADERS += \
    include/Systeme.h \
    include/particule.h \
    include/SousParticules.h \
    include/Vecteur3D.h \
    include/Enceinte.h \
    include/GenerateurAleatoire.h \
    include/Dessinable.h \
    include/support_a_dessin.h \
