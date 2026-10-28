#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "dessinable.h"
#include "support_a_dessin.h"
#include "SousParticules.h"
#include "Enceinte.h"

class GenerateurAletoire;

class Systeme : public Dessinable {

private:
    Enceinte enceinte_;
    std :: vector<std::unique_ptr<Particule>> ensemble_;
    GenerateurAleatoire tirage;
    const double EPSILON;
    double temperature_;
    const double dt_;
    
    // Méthodes :
    void test_choc(Particule& part, size_t i, GenerateurAleatoire& tirage);
    
public:
    // Constructeurs & destructeur :
    explicit Systeme(double longueur = 20, double largeur = 20, double hauteur = 20, double epsilon = 1, double temperature = 1, double dt = 1);
    virtual ~Systeme();
    Systeme( Systeme const& ) = delete;
    
    // Actions :
    void suppression();
    void ajoute_particule(Particule const& part);
    void affiche(std :: ostream& sortie) const;
    virtual void dessine_sur(SupportADessin& toile) const override;
		
    // Suppression de l'affectation :
    void operator = (Systeme const& a) = delete;
    
    // Simulation :
    void simulation(double const dt, SupportADessin& toile);
    void evolue(double dt);
    void mod_temp(double temp);
    // La méthode test_choc(...) est en privée mais fait aussi partie du bloc simulation
    
    // Initialisation :
    void initialisation_systeme();
    template<typename Part>
    void initialise(unsigned int n = 1);
};

std :: ostream& operator<<(std :: ostream& sortie, Systeme const& systeme);

// _____________________________________________________________________
// Initialisation :
template<typename Part>
void Systeme::initialise(unsigned int n) {
    if (n != 0) {
        for (unsigned int i(1); i <= n; ++i) {
            Part p;
            p.initialisation_particule(tirage, enceinte_.generation_position(tirage), temperature_);
            this -> ajoute_particule(p);
        }
    }
} // Avec cette méthode, on peut initialiser un grand nombre de particules et être sûrs que celles-ci auront une vitesse et une position adéquate. Pour l'utiliser : s.initialise<NomParticule>(NbreParticules);


