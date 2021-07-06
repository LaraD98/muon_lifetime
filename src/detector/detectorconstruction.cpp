#include "detector/detectorconstruction.h"

#include <G4Box.hh>
#include <G4FieldManager.hh>
#include <G4LogicalVolume.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>

namespace muon {

auto detector_construction::Construct() -> G4VPhysicalVolume*
{
    G4VSolid* world_solid { new G4Box{"World", 20.0 * cm, 10.0 * cm, 10.0 * cm} };

    // test material (liquid Argon)

    G4double density = 1.390 * g/cm3;
    G4double a = 39.95 * g/mole;
    G4double z = 18.;

    auto* detmat = new G4Material(
        "testMatieral",
        z,
        a,
        density
    );

    // auto* vacuum = new G4Material( // world is a vacuum
    //     "interGalactic",
    //     1.,
    //     1.008 * g / mole,
    //     1.e-25 * g / cm3,
    //     kStateGas,
    //     2.73 * kelvin,
    //     3.e-18 * pascal);

    auto* world_logical = new G4LogicalVolume(world_solid, detmat, "World");

    G4VPhysicalVolume* physical_world = new G4PVPlacement(
        nullptr,
        G4ThreeVector{},
        world_logical,
        "World",
        nullptr,
        false,
        0,
        true);
/*
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
*/
    G4VSolid* solid_layer { new G4Box{"atmosphere", 20.0 * cm, 10.0 * cm, 10.0 * cm} };
    auto* logical_volume { new G4LogicalVolume(solid_layer, detmat, "atmosphere") };
    [[maybe_unused]] auto* physical_layer { new G4PVPlacement{
        nullptr,
        G4ThreeVector{},
        logical_volume,
        "phys_layer",
        world_logical,
        false,
        0,
        true} };

    return physical_world;
}

}
