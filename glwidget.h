#pragma once

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QElapsedTimer>        // Classe pour gérer le temps
#include "vue_opengl.h"
#include "../general/include/Systeme.h"
#include "../general/include/Enceinte.h"
#include "../general/include/SousParticules.h"


class GLWidget : public QOpenGLWidget
{
public:
    GLWidget(QWidget* parent = nullptr);
    virtual ~GLWidget() = default;

private:
    // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
    virtual void initializeGL()                  override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL()                       override;

    // Méthodes de gestion d'évènements
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void timerEvent(QTimerEvent* event)  override;

    // Méthodes de gestion interne
    void pause();
    void re_initialize();

    // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
    VueOpenGL vue;

    // Timer :
    int timerId;
    
    // Pour faire évoluer les objets avec le bon "dt" .
    QElapsedTimer chronometre;

    // Objets à dessiner, faire évoluer :
    Systeme s;
};
