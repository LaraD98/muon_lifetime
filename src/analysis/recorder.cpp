#include "analysis/recorder.h"

#include <G4SystemOfUnits.hh>

#include <filesystem>
#include <fstream>
#include <iostream>

namespace muon {

recorder::recorder(std::string directory) noexcept
    : m_directory { std::move(directory) }
{
}

void recorder::reset(double energy)
{
    m_energy = energy;
}

void recorder::save(double range)
{
    m_data.emplace_back(range);
}

void recorder::save(double range, double d_e)
{
    m_deposit_data.emplace_back(dat{range, d_e});
}

void recorder::store()
{
    if (!std::filesystem::exists(m_directory)) {
        std::cout<<"data directory does not exist: Creating directory '"<<m_directory<<"'.\n";
        std::filesystem::create_directory(m_directory);
    }
    if (!m_data.empty()) {
    const std::string filename_base { m_directory + "/" + std::to_string(static_cast<int>(m_energy / CLHEP::keV)) + "_keV" };
    std::string filename { filename_base + ".dat" };
    std::size_t n { 1 };
    while (std::filesystem::exists(filename)) {
        filename = filename_base + "." + std::to_string(n) + ".dat";
        n++;
    }
    std::cout<<"Storing data in file '"<<filename<<"'\n";
    std::ofstream out { filename };

    for (const auto& data: m_data) {
        out<<data<<'\n';
    }
    out.close();
    }
    if (!m_deposit_data.empty()) {
    const std::string filename_base { m_directory + "/" + std::to_string(static_cast<int>(m_energy / CLHEP::keV)) + "_keV_deposit" };
    std::string filename { filename_base + ".dat" };
    std::size_t n { 1 };
    while (std::filesystem::exists(filename)) {
        filename = filename_base + "." + std::to_string(n) + ".dat";
        n++;
    }
    std::cout<<"Storing data in file '"<<filename<<"'\n";
    std::ofstream out { filename };

    for (const auto& [range, deposit]: m_deposit_data) {
        out<<range<<' '<<deposit<<'\n';
    }
    out.close();
    }


}

}
