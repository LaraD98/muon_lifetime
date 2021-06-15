#include "actions/actioninitialization.h"

#include <utility>

#include "actions/primarygeneratoraction.h"
#include "actions/trackingaction.h"
#include "actions/steppingaction.h"

namespace muon {

action_initialization::action_initialization(recorder& rec, double energy)
    : m_recorder { rec }
    , m_energy { std::move(energy) }
{
}

void action_initialization::BuildForMaster() const
{
}

void action_initialization::Build() const
{
    SetUserAction( new primary_generator_action { m_energy } );
    SetUserAction( new tracking_action{m_recorder} );
//    SetUserAction( new stepping_action{m_recorder} );
}
}
