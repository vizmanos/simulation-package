#pragma once

#include <deque>
#include <array>
typedef std::array<double,3> Vecteur;
class Enceinte;
class Argon;
class Helium;
class Neon;
class Systeme;
class Uranium;

class SupportADessin {
	
	public:
        SupportADessin()                                    = default;
	virtual ~SupportADessin()                           = default;
        SupportADessin(SupportADessin const&)               = delete;
        SupportADessin& operator=(SupportADessin const&)    = delete;
        SupportADessin(SupportADessin&&)                    = delete;
        SupportADessin& operator=(SupportADessin&&)         = delete;
        // On suppose ici que les supports ne seront ni copiés ni déplacés
        
        virtual void dessine(Enceinte const& enceinte) = 0;
        virtual void dessine(Argon const& ar) = 0;
        virtual void dessine(Neon const& ne) = 0;
        virtual void dessine(Helium const& he) = 0;
	virtual void dessine(Uranium const& ur) = 0;
	virtual void dessine(std::deque<Vecteur> const& positions) = 0;
};
