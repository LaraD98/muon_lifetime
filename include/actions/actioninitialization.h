#ifndef ACTIONINITIALIZATION_H
#define ACTIONINITIALIZATION_H

#include "global.h"
#include "analysis/recorder.h"

#include <G4VUserActionInitialization.hh>
#include <globals.hh>


namespace muon {

class action_initialization : public G4VUserActionInitialization {
public:
    explicit action_initialization(recorder& rec, double energy);

    void BuildForMaster() const override;
    void Build() const override;

private:
    recorder& m_recorder;

    double m_energy { 0.0 };
};
}

#endif // ACTIONINITIALIZATION_H
