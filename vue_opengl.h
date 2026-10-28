#pragma once

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "glsphere.h"
#include "support_a_dessin.h"
#include "../general/include/Enceinte.h"
#include "../general/include/particule.h"
#include "../general/include/SousParticules.h"
#include "../general/include/Systeme.h"


class VueOpenGL : public SupportADessin {
public:
    // Méthodes de dessin :
    virtual void dessine(Enceinte const& a_dessiner) override;
    virtual void dessine(Argon const& a_dessiner) override;
    virtual void dessine(Neon const& a_dessiner) override;
    virtual void dessine(Helium const& a_dessiner) override;
    virtual void dessine(Uranium const& a_dessiner) override;
    virtual void dessine(std::deque<Vecteur> const& positions) override;

    // Méthodes de (ré-)initialisation
    void init();
    void initializePosition();
    
    // Méthode set :
    void bind() { prog.bind(); }
    void setProjection(QMatrix4x4 const& projection)
    { prog.bind(); prog.setUniformValue("projection", projection); }

    // Méthodes set :
    void translate(double x, double y, double z);
    void rotate(double angle, double dir_x, double dir_y, double dir_z);
  
    // Dessins :
    void dessineCube(double hauteur, double largeur, double profondeur, QMatrix4x4 const& point_de_vue = QMatrix4x4() );
    void dessineSphere(QMatrix4x4 const& point_de_vue,
                         double rouge = 1.0, double vert = 1.0, double bleu = 1.0);
    
private:
    // Un shader OpenGL encapsulé dans une classe Qt :
    QOpenGLShaderProgram prog;

    // Caméra :
    QMatrix4x4 matrice_vue;
    
    // Sphère :
    GLSphere sphere;
    
    // Echelle :
    static constexpr double scale = 1.0;
};
