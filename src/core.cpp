#include "core.h"

#include <iostream>
#include <random>
#include <chrono>

#include "actions/actioninitialization.h"
#include "detector/detectorconstruction.h"


#include <QGSP_BERT.hh>

namespace muon {

application::application(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout<<"Wrong number of arguments. Usage:\n\tmuon_lifetime Energy(in MeV) n\n"<<std::flush;
        throw 1;
    }
    m_energy = std::stod(argv[1]) * MeV;
    m_n = std::stoi(argv[2]);
    std::cout<<"Using arguments: E = "<<m_energy<<" MeV, n = "<<std::to_string(m_n)<<'\n';
    m_recorder.reset(m_energy);
    setup();
}

application::~application()
{
    delete m_run_manager;
}

auto application::execute() -> int
{
    for (int i { 0 }; i < m_n; i++) {
        m_run_manager->BeamOn(1);
        std::cout<<std::to_string(i)<<'\r'<<std::flush;
    }
    std::cout<<'\n';
    m_recorder.store();
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

    m_run_manager->SetUserInitialization(new action_initialization { m_recorder, m_energy });

    m_run_manager->Initialize();
}
}
