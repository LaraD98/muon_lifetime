#include "actions/steppingaction.h"

#include <G4Step.hh>
#include <G4SystemOfUnits.hh>
#include <G4Track.hh>


namespace muon {

stepping_action::stepping_action(recorder& rec)
    : m_recorder { rec }
{
}

void stepping_action::UserSteppingAction(const G4Step* step)
{
    if (step->GetTrack()->GetTrackID() != 1) {
        return;
    }
    m_recorder.save(step->GetTrack()->GetTrackLength() / m,  step->GetTrack()->GetKineticEnergy() / keV );
}
}
