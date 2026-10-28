#pragma once
#include <string>
#include <cmath>
#include <memory>
#include "Vecteur3D.h"
#include "dessinable.h"
#include "support_a_dessin.h"
#include "Enceinte.h"
#include "GenerateurAleatoire.h"


class Particule : public Dessinable {
public:
    // Constructeur :
    Particule (const double masse, const Vecteur& position = {0,0,0}, const Vecteur& vitesse = {0,0,0});
    Particule (Particule const& part) = default;
    virtual ~Particule() = default;
    
    // Actions :
    virtual void affiche(std::ostream& sortie) const;
    virtual std::unique_ptr<Particule> copie() const = 0;
    Vecteur get_position() const;

    // Simulation :
    virtual void evolue(double dt);
    virtual void correction_enceinte(Enceinte const& enceinte, size_t j);
    bool compare_position(Particule const& part, double EPSILON);
    void choc_particule(Particule& part, GenerateurAleatoire& tirage, size_t i);
    void mod_vitesse(double temperature);
   
    // Initialisation
    void initialisation_particule(GenerateurAleatoire& tirage, Vecteur3D position, double const temperature);

protected:
    Vecteur3D position_;

private :
    const double masse_;
    Vecteur3D vitesse_;
};

std::ostream& operator<< (std::ostream& sortie, Particule const& particule);
