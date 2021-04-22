#include "actions/primarygeneratoraction.h"

#include <G4Event.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>
#include <G4MuonMinus.hh>

namespace muon {

primary_generator_action::primary_generator_action()
{
    m_gun.SetParticleDefinition(G4MuonMinus::Definition());
    m_gun.SetParticleEnergy(10 * MeV);
    m_gun.SetParticlePosition(G4ThreeVector{0.0, 0.0, 10'000.0 * km});
    m_gun.SetParticleMomentumDirection(G4ThreeVector{0., 0., -1.0});
}

primary_generator_action::~primary_generator_action() = default;

void primary_generator_action::GeneratePrimaries(G4Event* e)
{
    m_gun.GeneratePrimaryVertex(e);
}

}
