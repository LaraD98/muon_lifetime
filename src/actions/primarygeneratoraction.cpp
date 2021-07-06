#include "actions/primarygeneratoraction.h"

#include <G4Event.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>
#include <G4MuonMinus.hh>

namespace muon {

primary_generator_action::primary_generator_action(double energy)
{
    m_gun.SetParticleDefinition(G4Gamma::Definition());
    m_gun.SetParticleEnergy(energy);
    m_gun.SetParticlePosition(G4ThreeVector{0.0, 5.0 * cm, 5.0 * cm}); // gun in der Mitte von Grundfläche
    m_gun.SetParticleMomentumDirection(G4ThreeVector{1.0, 0., 0.}); // in x-Richtung 
}

primary_generator_action::~primary_generator_action() = default;

void primary_generator_action::GeneratePrimaries(G4Event* e)
{
    m_gun.GeneratePrimaryVertex(e);
}

}
