#include "detector/detectorconstruction.h"

#include <G4Box.hh>
#include <G4FieldManager.hh>
#include <G4LogicalVolume.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>

namespace muon {

auto detector_construction::Construct() -> G4VPhysicalVolume*
{
    G4VSolid* world_solid { new G4Box{"World", 100.0 * m, 100.0 * m, 10'000.0 * km} };

    auto* vacuum = new G4Material( // world is a vacuum
        "interGalactic",
        1.,
        1.008 * g / mole,
        1.e-25 * g / cm3,
        kStateGas,
        2.73 * kelvin,
        3.e-18 * pascal);

    auto* world_logical = new G4LogicalVolume(world_solid, vacuum, "World");

    G4VPhysicalVolume* physical_world = new G4PVPlacement(
        nullptr,
        G4ThreeVector{},
        world_logical,
        "World",
        nullptr,
        false,
        0,
        true);

    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

    G4VSolid* solid_layer { new G4Box{"atmosphere", 100.0 * m, 100.0 * m, 10'000.0 * km} };
    auto* logical_volume { new G4LogicalVolume(solid_layer, air, "atmosphere") };
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
