#include "include/particule.h"

using namespace std;

// _____________________________________________________________________
// Constructeur :
Particule::Particule(const double masse, const Vecteur &position, const Vecteur &vitesse)
    : masse_(masse), position_(position), vitesse_(vitesse) {}

// _____________________________________________________________________
// Actions:

void Particule::affiche(ostream &sortie) const
{
    sortie << " : pos : " << position_ << " ; v : " << vitesse_ << " ; m : " << masse_ << endl;
}

Vecteur Particule::get_position() const { return position_.getVecteur(); }

// _____________________________________________________________________
// Surcharge :
ostream &operator<<(ostream &sortie, Particule const &particule)
{
    particule.affiche(sortie);
    return sortie;
}

// _____________________________________________________________________
// Simulation :

void Particule::evolue(double dt)
{
    position_ += (vitesse_ * dt);
}

void Particule::correction_enceinte(Enceinte const &enceinte, size_t j)
{
    enceinte.choc_paroie(position_, vitesse_, j);
}

bool Particule::compare_position(Particule const &part, double EPSILON)
{
    return position_.compare_avec(part.position_, EPSILON);
}

void Particule::choc_particule(Particule &part, GenerateurAleatoire &tirage, size_t i)
{
    cout << "  avant le choc :" << endl;
    cout << "  *  part. " << i << " : : pos :" << position_ << " ; vit : " << vitesse_ << endl;
    cout << "  *  autre " << " : : pos : " << part.position_ << " ; vit : " << part.vitesse_ << endl;
    Vecteur3D Vitesse_g((vitesse_ * (masse_ / (masse_ + part.masse_))) + part.vitesse_ * (part.masse_ / (masse_ + part.masse_)));
    Vecteur3D Delta_vitesse(vitesse_ - Vitesse_g);
    double L = Delta_vitesse.norme();
    double z = tirage.uniforme(-L, L);
    double r = sqrt(pow(L, 2)) + pow(z, 2);
    double phi = tirage.uniforme(0, 2 * M_PI);
    Vecteur3D Vo(r * cos(phi), r * sin(phi), 0);
    vitesse_ = (Vitesse_g + Vo);
    part.vitesse_ = Vitesse_g - (Vo * (masse_ / part.masse_));

    cout << "  après le choc :" << endl;
    cout << "  *  part. " << i << " : : pos :" << position_ << " ; vit : " << vitesse_ << endl;
    cout << "  *  autre " << " : : pos : " << part.position_ << " ; vit : " << part.vitesse_ << endl;
}

void Particule::mod_vitesse(double temperature)
{
    const double R = 8.314472;
    const double kg_mol = masse_ / 1000;
    vitesse_ = Vecteur3D(sqrt((R * temperature) / kg_mol), sqrt((R * temperature) / kg_mol), sqrt((R * temperature) / kg_mol));
}

// _____________________________________________________________________
// Initialisation :
void Particule::initialisation_particule(GenerateurAleatoire &tirage, Vecteur3D position, double const temperature)
{
    position_ = position;
    const double R = 8.314472;
    const double kg_mol = masse_ / 1000;
    Vecteur v;
    for (auto &coord : v)
    {
        coord = tirage.gaussienne(0.0, sqrt((R * temperature) / kg_mol));
    }
    vitesse_ = Vecteur3D(v);
}
