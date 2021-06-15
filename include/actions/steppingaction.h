#ifndef STEPPINGACTION_H
#define STEPPINGACTION_H

#include "global.h"
#include "analysis/recorder.h"

#include <G4SystemOfUnits.hh>

#include <G4Types.hh>
#include <G4UserSteppingAction.hh>

class G4Step;

namespace muon {

class stepping_action : public G4UserSteppingAction {
public:
    stepping_action(recorder& rec);

    void UserSteppingAction(const G4Step* step) override;

private:
    recorder& m_recorder;
};
}

#endif // STEPPINGACTION_H
