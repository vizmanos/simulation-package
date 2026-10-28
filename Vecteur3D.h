#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <cmath>


typedef std::array<double,3> Vecteur;

class Vecteur3D {
	
private:
    // Attributs :
    Vecteur vecteur_;
    static constexpr double alpha = 1e-10;
        
    // Méthodes :
    void modification(size_t i, double borne_sup = 0);
    
public:
    // Accesseurs :
    Vecteur getVecteur() const;
    
    // Constructeurs & destructeur:
    explicit Vecteur3D(double x = 0.0, double y = 0.0, double z = 0.0);
    Vecteur3D(Vecteur const& vecteur);
    Vecteur3D(Vecteur3D const& vect) = default;
    virtual ~Vecteur3D() {}
    
    // Actions :
    double prod_scal(Vecteur3D v2) const;
    double norme2() const;
    double norme() const;
    double prod_explicit(Vecteur3D const& v2, int n) const;
    void affiche(std :: ostream& sortie) const;
		
    // Opérateurs :
    bool operator==(Vecteur3D const& vect) const;
    Vecteur3D& operator+=(Vecteur3D const& v2);
    Vecteur3D& operator-=(Vecteur3D const& v2);
    Vecteur3D& operator*=(double x);
    Vecteur3D& operator=(Vecteur3D const& vect) = default;
    
    // Simulation :
    void test_choc_paroi(Vecteur3D& vect, double l, double p, double h, size_t i);
    bool compare_avec(Vecteur3D const& p2, double EPSILON);
};

// Autres méthodes/fonctions :
std :: ostream& operator<<(std :: ostream& sortie, const Vecteur3D& vect);
bool operator!=(Vecteur3D const& vect1, Vecteur3D const& vect2);
Vecteur3D operator+(Vecteur3D v1, Vecteur3D const& v2);
Vecteur3D operator-(Vecteur3D v1, Vecteur3D const& v2);
Vecteur3D operator*(Vecteur3D vect, double x);
Vecteur3D operator^(Vecteur3D const& v1, Vecteur3D const& v2);
