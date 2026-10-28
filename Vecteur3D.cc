#include "include/Vecteur3D.h"

using namespace std;

// _____________________________________________________________________
// Constructeurs :
Vecteur3D :: Vecteur3D(double x, double y, double z)
: vecteur_{x,y,z} {}
Vecteur3D :: Vecteur3D(Vecteur const& vect)
: vecteur_(vect) {}
// _____________________________________________________________________
// Accesseurs :

Vecteur Vecteur3D :: getVecteur() const {return vecteur_; }

// _____________________________________________________________________
// Actions :

double Vecteur3D :: prod_scal(Vecteur3D v2) const {
	
	double prod(0);
	
	for (size_t i(0); i < 3; ++i) {
		prod += vecteur_[i] * v2.vecteur_[i];
	}
	return prod;
}
double Vecteur3D :: norme2() const {
	
	double n2(0);
	
		n2 = pow(vecteur_[0],2.0) + pow(vecteur_[1],2.0) + pow(vecteur_[2],2.0);
	
	return n2;
}
double Vecteur3D :: norme() const {
	
	return sqrt(norme2());
}
double Vecteur3D :: prod_explicit(Vecteur3D const& v2, int n) const {
	
	switch(n) {
		case 0:
			return vecteur_[1] * v2.vecteur_[2] - vecteur_[2] * v2.vecteur_[1];
		case 1:
			return vecteur_[2] * v2.vecteur_[0] - vecteur_[0] * v2.vecteur_[2];
		case 2:
			return vecteur_[0] * v2.vecteur_[1] - vecteur_[1] * v2.vecteur_[0];
		default:
			return 0;
	}
}
void Vecteur3D :: affiche(ostream& sortie) const {
    for (auto const& coord : vecteur_) {
        sortie << coord << " ";
    }
}
void Vecteur3D :: modification(size_t i, double borne_sup) {
    vecteur_[i] = 2 * borne_sup - vecteur_[i];
}

// _____________________________________________________________________
// Surcharge interne :

bool Vecteur3D :: operator==(Vecteur3D const& vect) const {
	unsigned int n(0);
	for (int i(0); i <= 2; ++i) {
		if (abs(vecteur_[i] - vect.vecteur_[i]) < alpha) ++n;
	}
	return (n == 3);
}

Vecteur3D& Vecteur3D :: operator+=(Vecteur3D const& v2) {
	
	for (size_t i(0); i < 3 ; ++i) {
		vecteur_[i] += v2.vecteur_[i];
	}
	return *this;
}

Vecteur3D& Vecteur3D :: operator-=(Vecteur3D const& v2) {

	for (size_t i(0); i < 3 ; ++i) {
		vecteur_[i] -= v2.vecteur_[i];
	}
	return *this;
}

Vecteur3D& Vecteur3D :: operator*=(double x) {
	
	for (size_t i(0); i < 3 ; ++i) {
		vecteur_[i] *= x;
	}
	return *this;
}

// _____________________________________________________________________
//Simulation

void Vecteur3D::test_choc_paroi(Vecteur3D& vit, double largeur, double profondeur, double hauteur, size_t j) {
    const Vecteur limite = {largeur, profondeur, hauteur};
    for (size_t k(0); k < 3; ++k) {
        if (vecteur_[k] < 0) {
            modification(k);
            vit.modification(k); // En privée car dans la même classe
            cout << "La particule " << j+1 << " rebondit sur la face " << k+1 << endl;
        } else if (vecteur_[k] > limite[k]) {
            modification(k,limite[k]);
            vit.modification(k);
            cout << "La particule " << j+1 << " rebondit sur la face " << k+4 << endl;
        }
    }
}

bool Vecteur3D::compare_avec(Vecteur3D const& p2, double EPSILON) {
    unsigned int n(0);
    for (size_t l(0); l < 3; ++l) {
        if ((floor(vecteur_[l] / EPSILON)) == (floor(p2.vecteur_[l] / EPSILON))) ++n;
    }
    return (n == 3);
}

// _____________________________________________________________________
// Surcharge externe :

ostream& operator<<(ostream& sortie, Vecteur3D const& vect) {
    vect.affiche(sortie);
	return sortie;
}

bool operator!=(Vecteur3D const& vect1, Vecteur3D const& vect2) {
	return !(vect1 == vect2);
}

Vecteur3D operator+(Vecteur3D v1, Vecteur3D const& v2) {
	return v1 += v2;
}

Vecteur3D operator-(Vecteur3D v1, Vecteur3D const& v2) {
	return v1 -= v2;
}

Vecteur3D operator*(Vecteur3D vect, double x) {
    return vect *= x;
}

Vecteur3D operator^(Vecteur3D const& v1, Vecteur3D const& v2) {
	Vecteur3D v3(v1.prod_explicit(v2, 0), v1.prod_explicit(v2, 1), v1.prod_explicit(v2, 2) );
	return v3;
}
