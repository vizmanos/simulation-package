#pragma once
#include "particule.h"
#include <memory>
#include <deque>

// _____________________________________________________________________

class Neon : public Particule {
private:
    static constexpr double masse = 20.1797;
public:
    // Constructeurs & destructeur :
    Neon(const Vecteur& vitesse = {0,0,0}, const Vecteur& position = {0,0,0});
    explicit Neon(Neon const& ne) = default;
    virtual ~Neon() = default;
    
    // Actions :
    virtual void affiche(std::ostream&) const override;
    virtual std::unique_ptr<Particule> copie() const override;
    virtual void dessine_sur(SupportADessin& toile) const override;
};

// _____________________________________________________________________

class Helium : public Particule {
private:
    static constexpr double masse = 4.002602;
public:
    // Constructeurs & destructeur :
    Helium(const Vecteur& vitesse = {0,0,0}, const Vecteur& position = {0,0,0});
    explicit Helium(Helium const& ne) = default;
    virtual ~Helium() = default;
    
    // Actions :
    virtual void affiche(std::ostream&) const override;
    virtual std::unique_ptr<Particule> copie() const override;
    virtual void dessine_sur(SupportADessin& toile) const override;
};

// _____________________________________________________________________

class Argon : public Particule {
private:
    static constexpr double masse = 39.948;
public:
    // Constructeur & destructeur :
    Argon(const Vecteur& vitesse = {0,0,0}, const Vecteur& position = {0,0,0});
    explicit Argon(Argon const& ne) = default;
    virtual ~Argon() = default;
    
    // Actions :
    virtual void affiche(std::ostream&) const override;
    virtual std::unique_ptr<Particule> copie() const override;
    virtual void dessine_sur(SupportADessin& toile) const override;
};

// _____________________________________________________________________

class Uranium : public Particule {
private:
    static constexpr double masse = 238.02891;
    std::deque<Vecteur> points_memorises;
public:
    // Constructeur & destructeur :
    Uranium(const Vecteur& vitesse = {0,0,0}, const Vecteur& position = {0,0,0});
    explicit Uranium(Uranium const& ne) = default;
    virtual ~Uranium() = default;
    
    // Actions :
    virtual void affiche(std::ostream&) const override;
    virtual std::unique_ptr<Particule> copie() const override;
    virtual void dessine_sur(SupportADessin& toile) const override;
    virtual void correction_enceinte(Enceinte const& enceinte, size_t j) override;
    virtual void evolue(double dt) override;
    void ajoute_position();
    
};

