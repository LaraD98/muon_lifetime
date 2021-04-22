#ifndef CORE_H
#define CORE_H

#include "global.h"
#include "analysis/recorder.h"

#include <G4RunManager.hh>

#include <string>
#include <memory>



namespace muon {
class application {
public:
    application(int argc, char* argv[]);

    virtual ~application();

    auto execute() -> int;

private:
    void setup();

    G4RunManager* m_run_manager { nullptr };

    recorder m_recorder {"data"};
};
}
#endif // CORE_H
