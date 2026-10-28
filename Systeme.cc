#include "include/Systeme.h"

using namespace std;

// _____________________________________________________________________
// Constructeurs & destructeur :
Systeme::Systeme(double longueur, double largeur, double hauteur, double epsilon, double temperature, double dt)
: enceinte_(Enceinte(longueur, largeur, hauteur)), EPSILON(epsilon), temperature_(temperature), dt_(dt) {}
Systeme::~Systeme() {
    ensemble_.clear();
}

// _____________________________________________________________________
// Actions :
void Systeme::suppression() {
        ensemble_.clear();
}
void Systeme::ajoute_particule(Particule const& part) {
    ensemble_.push_back(part.copie());
}
void Systeme::affiche(ostream& sortie) const {
    sortie <<"Le système est ";
    if  (ensemble_.size() == 0) {
        sortie << "vide" << endl;
    } else {
        if (ensemble_.size() == 1) {
            sortie << "constitué de la particule suivante : " << endl;
            sortie << *ensemble_[0];
        } else {
            sortie << " constitué des particules suivantes : " << endl << endl;
            for (auto const& p : ensemble_) {
                sortie <<" particule " << *p; }
        }
    }
    cout << endl;
}
void Systeme::dessine_sur(SupportADessin& toile) const {
    enceinte_.dessine_sur(toile);
    
    for(auto const& part : ensemble_) {
        part -> dessine_sur(toile);
    }
}

ostream& operator<<(ostream& sortie,Systeme const& systeme) {
    systeme.affiche(sortie);
    return sortie;
}

// _____________________________________________________________________
// Simulation :
void Systeme::evolue(double dt) {
    // Evolution des particules
    for (size_t j(0); j < ensemble_.size(); ++j) {
        ensemble_[j] -> evolue(dt);
        ensemble_[j] -> correction_enceinte(enceinte_, j);
    }
    // Gestion des chocs
    for (size_t j(0); j < ensemble_.size(); ++j) {
        test_choc(*ensemble_[j], j, tirage);
    }
}

void Systeme::test_choc(Particule& part, size_t j, GenerateurAleatoire& tirage) {
    if ( j == ensemble_.size() - 1 );
    else {
        bool test(false);
        size_t i(j);
        while((i < ensemble_.size() - 1) && !test){
            test = part.compare_position(*ensemble_[i+1], EPSILON);
            ++i;
            // En parcourant ainsi la liste, on diminue le nombre de chocs possibles
        }
        if (test) { // Si la distance entre les particules < EPSILON appel de la fonction choc_particule
            cout << "La particule " << j+1 << " rentre en collision avec une autre particule." << endl;
            ensemble_[i]->choc_particule(part, tirage, j+1);
        }
    }
}

void Systeme::simulation(double const dt, SupportADessin& toile) {
    this -> dessine_sur(toile);
    cout << "Lancement de la simulation :" << endl << endl;
    for (size_t p(0); p < 10; ++p) {
        evolue(dt);
        for (auto const& part : ensemble_){
            part -> dessine_sur(toile); cout << " particule " << *part;
        }
        cout << "===================================================" << endl;
    }
    cout << "Fin de la simulation" << endl;
}

void Systeme::mod_temp(double temp) {
   temperature_ += temp;
   // initialisation_systeme(); //Aucun sens d'initialiser le programme à nouveau
   // En modifiant la température, les vitesses que peuvent prendre les particules est modifiée : augmentation température => vitesse plus élevée et vice-versa.
}

// _____________________________________________________________________
// Initialisation :
void Systeme::initialisation_systeme() {
    for ( auto const& part: ensemble_) {
        part->initialisation_particule(tirage, enceinte_.generation_position(tirage), temperature_);
    }
}


