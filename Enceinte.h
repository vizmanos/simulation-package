#pragma once
#include "dessinable.h"
#include "support_a_dessin.h"
#include "Vecteur3D.h"
#include "GenerateurAleatoire.h"
#include <iostream>

class Enceinte : public Dessinable {
	
private:
    double hauteur_;
    double largeur_;
    double profondeur_;
	
public:
    // Constructeur & destructeur :
    Enceinte(double h = 20, double l = 20, double p = 20);
    Enceinte(Enceinte const& enceinte) = default;
    virtual ~Enceinte() = default;
		
    // Actions :
    double vol() const;
    virtual void dessine_sur(SupportADessin& toile) const override;
    void affiche(std::ostream& sortie) const;
    Vecteur get_limites() const {return Vecteur({hauteur_, largeur_, profondeur_});}
        
    // Simulation :
    void choc_paroie(Vecteur3D& pos, Vecteur3D& vit, size_t j) const;
   
    // Generateur position :
    Vecteur3D generation_position(GenerateurAleatoire& tirage) const;
};

std::ostream& operator<<(std::ostream& sortie, Enceinte const& enceinte);
