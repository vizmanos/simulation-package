#include <iostream>
#include "include/SousParticules.h"
using namespace std;

//____________________________________________
//Classe Argon :

Argon::Argon(const Vecteur& position, const Vecteur& vitesse)
		: Particule(masse, position, vitesse) {}
unique_ptr<Particule> Argon::copie() const {
	return unique_ptr<Particule> (new Argon(*this)); // Copie profonde qui va être utilisée pour l'ensemble des particules
}
void Argon::affiche(ostream& sortie) const {
    sortie << "Argon ";
    Particule::affiche(sortie);
}
void Argon::dessine_sur(SupportADessin& toile) const {
    toile.dessine(*this);
}

//____________________________________________
// Classe Neon :

Neon::Neon(const Vecteur& position, const Vecteur& vitesse)
		: Particule(masse, position, vitesse) {}
unique_ptr<Particule> Neon::copie() const {
	return unique_ptr<Particule> (new Neon(*this));
}
void Neon::affiche(ostream& sortie) const {
    sortie << "Néon ";
    Particule::affiche(sortie);
}
void Neon::dessine_sur(SupportADessin& toile) const {
    toile.dessine(*this);
}

//____________________________________________
// Classe Helium :

Helium::Helium(const Vecteur& position, const Vecteur& vitesse)
		: Particule(masse, position, vitesse) {}
unique_ptr<Particule> Helium::copie() const {
	return unique_ptr<Particule> (new Helium(*this));
}
void Helium::affiche(ostream& sortie) const {
    sortie << "Hélium ";
    Particule::affiche(sortie);
}
void Helium::dessine_sur(SupportADessin& toile) const {
    toile.dessine(*this);
}

//____________________________________________
// Classe Uranium :

Uranium :: Uranium(const Vecteur& position, const Vecteur& vitesse)
		: Particule(masse, position, vitesse) {}
unique_ptr<Particule> Uranium ::copie() const {
	return unique_ptr<Particule> (new Uranium (*this));
}
void Uranium ::affiche(ostream& sortie) const {
    sortie << "Uranium ";
    Particule::affiche(sortie);
}
void Uranium::dessine_sur(SupportADessin& toile) const {
  toile.dessine(points_memorises);
  toile.dessine(*this);
}
void Uranium::correction_enceinte(Enceinte const& enceinte, size_t j) {
    Particule::correction_enceinte(enceinte,j);
    ajoute_position();
}
void Uranium::evolue(double dt) {
    Particule::evolue(dt);
    ajoute_position();
}
void Uranium::ajoute_position() {
 if (points_memorises.size() > 250) points_memorises.pop_front();
 else points_memorises.push_back(position_.getVecteur());
}

