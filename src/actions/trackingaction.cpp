#include "actions/trackingaction.h"

#include <G4Track.hh>
#include <G4SystemOfUnits.hh>

namespace muon {

tracking_action::tracking_action(recorder& rec)
    : m_recorder { rec }
{
}

void tracking_action::PostUserTrackingAction(const G4Track* track)
{
    if (track->GetTrackID() != 0) {
        return;
    }
    m_recorder.save( track->GetTrackLength() / m );
}

}
