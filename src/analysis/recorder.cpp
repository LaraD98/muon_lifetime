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
    constexpr static double E_0 { 105.6583755 * CLHEP::MeV }; // rest energy of µ
    constexpr static double tau { 2.1969811 * CLHEP::microsecond }; // mean lifetime of µ
    constexpr static double c_0 { 299'792'458.0e-9 }; // speed of light in m/ns
    const double gamma { energy / E_0 + 1.0 }; // Lorentz factor of the µ with kinetic energy
    const double T_0 { tau / gamma };  // lifetime of the µ in laboratory system
    const double range { T_0 * c_0 }; // expected range of µ

    m_histogram.reset(0.0, range * 5.0); // reset the histogram so it can store values up to a range of 5 times the expected range
}

void recorder::save(double range)
{
    m_histogram.add(range);
}

void recorder::store()
{
    if (!std::filesystem::exists(m_directory)) {
        std::cout<<"data directory does not exist: Creating directory '"<<m_directory<<"'.\n";
        std::filesystem::create_directory(m_directory);
    }
    const std::string filename_base { m_directory + "/" + std::to_string(static_cast<int>(m_energy / CLHEP::keV)) + "_keV" };
    std::string filename { filename_base + ".hist" };
    std::size_t n { 1 };
    while (std::filesystem::exists(filename)) {
        filename = filename_base + "." + std::to_string(n) + ".hist";
    }
    std::cout<<"Storing histogram in file '"<<filename<<"'\n";
    std::ofstream out { filename };

    for (const auto& bin: m_histogram.qualified_bins()) {
        out<<((bin.lower + bin.upper)/2.0)<<' '<<std::to_string(bin.count)<<'\n';
    }
    out.close();
}

}
