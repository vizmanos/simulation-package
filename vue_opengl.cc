#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs

// ======================================================================
void VueOpenGL::dessine(Enceinte const& e)
{
    Q_UNUSED(e);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    dessineCube(e.get_limites()[0], e.get_limites()[1], e.get_limites()[2]);
}

void VueOpenGL::dessine(Argon const& ar)
{
    QMatrix4x4 matrice;
    matrice.setToIdentity();
    
    matrice.translate(ar.get_position()[0], ar.get_position()[1], ar.get_position()[2]);
    matrice.scale(scale*0.2);
    dessineSphere(matrice, 1.0, 0.0, 0.0);
}

void VueOpenGL::dessine(Neon const& ne)
{     
   QMatrix4x4 matrice;
   matrice.setToIdentity();
    
   matrice.translate(ne.get_position()[0], ne.get_position()[1], ne.get_position()[2]);
   matrice.scale(scale*0.2);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   dessineSphere(matrice, 0.0, 1.0, 0.0);
}

void VueOpenGL::dessine(Helium const& he)
{  
   QMatrix4x4 matrice;
   matrice.setToIdentity();
    
   matrice.translate(he.get_position()[0], he.get_position()[1], he.get_position()[2]);
   matrice.scale(scale*0.2);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   dessineSphere(matrice, 0.0, 0.0, 1.0);
}

void VueOpenGL::dessine(Uranium const& ur)
{   
   QMatrix4x4 matrice;
   matrice.setToIdentity();
   
   matrice.translate(ur.get_position()[0], ur.get_position()[1], ur.get_position()[2]);
   matrice.scale(scale*0.2);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   dessineSphere(matrice, 1.0, 1.0, 1.0); 
}

void VueOpenGL::dessine(std::deque<Vecteur> const& positions)
{
   QMatrix4x4 matrice;
   matrice.setToIdentity();
   matrice.scale(scale);
   prog.setUniformValue("vue_modele", matrice_vue * matrice);
   prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
   // On réinitialise la vue et la couleur pour que les traits soient bien dessinés
   
   glBegin(GL_LINE_STRIP);
   for (auto const& point : positions) {
        glVertex3f(point[0], point[1], point[2]);
   }
   glEnd();
}

// ======================================================================
void VueOpenGL::init()
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

    prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
    prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

    /* Identifie les deux attributs du shader de cet exemple
    * (voir vertex_shader.glsl).
    *
    * L'attribut identifié par 0 est particulier, il permet d'envoyer un
    * nouveau "point" à OpenGL
    *
    * C'est pourquoi il devra obligatoirement être spécifié et en dernier
    * (après la couleur dans cet exemple, voir plus bas).
    */

    prog.bindAttributeLocation("sommet",  SommetId);
    prog.bindAttributeLocation("couleur", CouleurId);

    // Activation du shader
    prog.bind();

    /* Activation du "Test de profondeur" et du "Back-face culling"
     * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
     * partielement caché par d'autres objets.
     *
     * Le Back-face culling consiste à ne dessiner que les face avec ordre
     * de déclaration dans le sens trigonométrique.
     */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	
    sphere.initialize();
    initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
  matrice_vue.setToIdentity();
  matrice_vue.translate(-10.0, -12.0, -40.0);
  matrice_vue.rotate(30.0, 0.0, 1.0, 0.0);
  matrice_vue.rotate(20.0, 0.0, 0.0, 1.0);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::dessineCube (double h, double l, double p, QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(SommetId, h, 0.0, 0.0);
  prog.setAttributeValue(SommetId, h, h, 0.0);
  prog.setAttributeValue(SommetId, h, h, h);
  prog.setAttributeValue(SommetId, h, 0, h);

  // face coté X = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 0.0, h);
  prog.setAttributeValue(SommetId, 0.0, h, h);
  prog.setAttributeValue(SommetId, 0.0, h, 0.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, 0.0, l, 0.0);
  prog.setAttributeValue(SommetId, 0.0, l, l);
  prog.setAttributeValue(SommetId, l, l, l);
  prog.setAttributeValue(SommetId, l, l, 0.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 1.0); // cyan
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, l, 0.0, 0.0);
  prog.setAttributeValue(SommetId, l, 0.0, l);
  prog.setAttributeValue(SommetId, 0.0, 0.0, l);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0); // jaune
  prog.setAttributeValue(SommetId, 0.0, 0.0, p);
  prog.setAttributeValue(SommetId, p, 0.0, p);
  prog.setAttributeValue(SommetId, p, p, p);
  prog.setAttributeValue(SommetId, 0.0, p, p);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); // magenta
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, p, 0.0);
  prog.setAttributeValue(SommetId, p, p, 0.0);
  prog.setAttributeValue(SommetId, p, 0.0, 0.0);

  glEnd();
}

void VueOpenGL::dessineSphere(QMatrix4x4 const& point_de_vue,
                              double rouge, double vert, double bleu) {
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    prog.setAttributeValue(CouleurId, rouge, vert, bleu);
    sphere.draw(prog, SommetId);
}
