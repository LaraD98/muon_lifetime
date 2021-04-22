#ifndef DETECTORCONSTRUCTION_H
#define DETECTORCONSTRUCTION_H

#include "global.h"

#include <G4VUserDetectorConstruction.hh>
#include <globals.hh>

#include <G4Box.hh>
#include <G4Material.hh>
#include <G4SystemOfUnits.hh>

class G4VPhysicalVolume;

namespace muon {
class detector_construction : public G4VUserDetectorConstruction {
public:
    ~detector_construction() override = default;

    auto Construct() -> G4VPhysicalVolume* override;
};
}

#endif // DETECTORCONSTRUCTION_H
