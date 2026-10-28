#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "glwidget.h"

// ======================================================================
GLWidget::GLWidget(QWidget* parent)
  : QOpenGLWidget(parent), s(100.0,100.0,100.0, 0.5, 0.5)
{ 
    chronometre.restart();
    
    s.initialise<Argon>(300);
    s.initialise<Neon>(300);
    s.initialise<Helium>(400);
    s.initialise<Uranium>(2);
    // Por visualiser le mouvement Brownien, décomenter la ligne précécente (s.initialise<Uranium>(2);)
}

// ======================================================================
void GLWidget::initializeGL()
{
  vue.init();
  timerId = startTimer(20);
}

// ======================================================================
void GLWidget::resizeGL(int width, int height) // Méthode donnée
{
  glViewport(0, 0, width, height);
  QMatrix4x4 matrice;
  matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
  vue.setProjection(matrice);
}

// ======================================================================
void GLWidget::paintGL()
{
  vue.bind();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  s.dessine_sur(vue);
}


// ======================================================================
void GLWidget::keyPressEvent(QKeyEvent* event)
{
  constexpr double petit_angle(15.0); // En degrés
  constexpr double petit_pas(2.0);

  switch (event->key()) {

  case Qt::Key_Left:
    vue.rotate(petit_angle, 0.0, -0.2, 0.0);
    break;

  case Qt::Key_Right:
    vue.rotate(petit_angle, 0.0, +0.2, 0.0);
    break;

  case Qt::Key_Up:
    vue.rotate(petit_angle, -1.0, 0.0, 0.0);
    break;

  case Qt::Key_Down:
    vue.rotate(petit_angle, +1.0, 0.0, 0.0);
    break;

  case Qt::Key_PageUp:
  case Qt::Key_W:
    vue.translate(0.0, 0.0,  petit_pas);
    break;

  case Qt::Key_PageDown:
  case Qt::Key_S:
    vue.translate(0.0, 0.0, -petit_pas);
    break;

  case Qt::Key_A:
    vue.translate( petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_D:
    vue.translate(-petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_R:
    vue.translate(0.0, -petit_pas, 0.0);
    break;

  case Qt::Key_F:
    vue.translate(0.0,  petit_pas, 0.0);
    break;

  case Qt::Key_Q:
    vue.rotate(petit_angle, 0.0, 0.0, -1.0);
    break;

  case Qt::Key_E:
    vue.rotate(petit_angle, 0.0, 0.0, +1.0);
    break;

  case Qt::Key_Home:
    vue.initializePosition();
    break;

  case Qt::Key_Space:
    pause();
    break;
  
  case Qt::Key_O:
    s.mod_temp(+0.05); // Augmentation de la température
    break;
  
  case Qt::Key_L:
    s.mod_temp(-0.05); // Diminution de la température
    break;
  
  case Qt::Key_Return:
    re_initialize();
    break;
  };
  
  update();
}

// ======================================================================
void GLWidget::timerEvent(QTimerEvent* event)
{
  Q_UNUSED(event);
  const double dt = chronometre.elapsed() / 1000.0;
  chronometre.restart();

  s.evolue(dt);
  update();
}

// ======================================================================
void GLWidget::pause()
{
  if (timerId == 0) {
	// dans ce cas le timer ne tourne pas alors on le lance
	timerId = startTimer(20);
	chronometre.restart();
  } else {
	// le timer tourne alors on l'arrête
	killTimer(timerId);
	timerId = 0;
  }
}

void GLWidget::re_initialize() // Pour ré-initialiser le système sans avoir à sortir de la simulation
{
   s.initialisation_systeme();
   update();
}
