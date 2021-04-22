#ifndef PRIMARYGENERATORACTION_H
#define PRIMARYGENERATORACTION_H

#include <G4ParticleGun.hh>
#include <G4SystemOfUnits.hh>
#include <G4VUserPrimaryGeneratorAction.hh>
#include <globals.hh>

#include "global.h"

class G4ParticleGun;
class G4Event;
class G4Box;

namespace muon {

class recorder;

class primary_generator_action : public G4VUserPrimaryGeneratorAction {
public:
    primary_generator_action();

    ~primary_generator_action() override;

    void GeneratePrimaries(G4Event* e) override;

private:
    G4ParticleGun m_gun { 1 };
};
}

#endif // PRIMARYGENERATORACTION_H
