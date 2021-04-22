#ifndef TRACKING_ACTION_H
#define TRACKING_ACTION_H

#include "analysis/recorder.h"

#include <G4UserTrackingAction.hh>

class G4Track;

namespace muon {

class tracking_action :  public G4UserTrackingAction
{
public:
    tracking_action(recorder& rec);

    void PostUserTrackingAction(const G4Track* track) override;

private:
    recorder& m_recorder;
};

}

#endif // TRACKING_ACTION_H
