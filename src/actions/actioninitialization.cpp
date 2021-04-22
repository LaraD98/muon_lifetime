#include "actions/actioninitialization.h"

#include <utility>

#include "actions/primarygeneratoraction.h"

namespace muon {

action_initialization::action_initialization(recorder& rec)
    : m_recorder { rec }
{
}

void action_initialization::BuildForMaster() const
{
}

void action_initialization::Build() const
{
    SetUserAction( new primary_generator_action {} );
}
}
