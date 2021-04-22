#include "core.h"

#include <iostream>
#include <random>
#include <chrono>

#include "actions/actioninitialization.h"
#include "detector/detectorconstruction.h"
#include "physics/physicslist.h"

#include "cancelcriterion.h"

#include <QGSP_BERT.hh>

namespace muon {

application::application(int argc, char* argv[])
{
    setup();
}

application::~application()
{
    delete m_run_manager;
}

auto application::execute() -> int
{
    m_run_manager->BeamOn(1);
    return 0;
}

void application::setup()
{
    std::random_device rd;
    std::mt19937::result_type initial_seed = rd() ^ (static_cast<std::mt19937::result_type>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()) + static_cast<std::mt19937::result_type>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()));

    std::mt19937 gen(initial_seed);
    std::uniform_int_distribution<G4long> distribution;

    constexpr size_t max_seeds { 4 };

    std::array<G4long, max_seeds> seeds {};

    for (auto& seed : seeds) {
        seed = distribution(gen);
    }

    CLHEP::HepRandom::setTheSeeds(seeds.data());

    m_run_manager = new G4RunManager {};

    m_run_manager->SetVerboseLevel(0);

    m_run_manager->SetUserInitialization( new QGSP_BERT{} );

    m_run_manager->SetUserInitialization(new detector_construction {});

    m_run_manager->SetUserInitialization(new action_initialization { m_recorder });

    m_run_manager->Initialize();
}
}
