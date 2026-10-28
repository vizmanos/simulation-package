#include <iostream>
#include "include/Enceinte.h"
using namespace std;

// _____________________________________________________________________
// Constructeur & destructeur :

Enceinte::Enceinte(double h, double l, double p)
: hauteur_(h), largeur_(l), profondeur_(p) {}

// _____________________________________________________________________
// Actions :

double Enceinte::vol() const { return hauteur_*largeur_*profondeur_; }
void Enceinte::dessine_sur(SupportADessin& toile) const { toile.dessine(*this); }
void Enceinte::affiche(ostream& sortie) const {
	sortie << "Enceinte de largeur :" << largeur_ << ", de profondeur : " << profondeur_ << " et de hauteur : " << hauteur_ << endl;
}

// _____________________________________________________________________
// Simulation :

void Enceinte::choc_paroie(Vecteur3D& pos, Vecteur3D& vit, size_t j) const {
    pos.test_choc_paroi(vit, largeur_, profondeur_, hauteur_, j);
}

// _____________________________________________________________________
// Surcharge :
ostream& operator<<(ostream& sortie, Enceinte const& enceinte) {
    enceinte.affiche(sortie);
    return sortie;
}

// _____________________________________________________________________
// Generateur position :
Vecteur3D Enceinte::generation_position(GenerateurAleatoire& tirage) const{
    return Vecteur3D(tirage.uniforme(0, hauteur_), tirage.uniforme(0, largeur_), tirage.uniforme(0,profondeur_));
}

