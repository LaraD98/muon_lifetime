#ifndef RECORDER_H
#define RECORDER_H

#include "global.h"
#include "analysis/histogram.h"

#include <string>

namespace muon {

class recorder {
public:
    explicit recorder(std::string directory) noexcept;

    void reset(double energy);

    void save(double range);
    void save(double range, double d_e);

    void store();

private:
    constexpr static std::size_t s_n_bins { 2000 };

    std::string m_directory {};
    double m_energy {};

    std::vector<double> m_data {};
    struct dat
    {
        double range {};
        double d_e {};
    };

    std::vector<dat> m_deposit_data {};
};
}

#endif // RECORDER_H
