#pragma once

#include "Model/ContainerLoadingInstance.h"
#include "Model/Node.h"
#include "Model/Container.h"


#include <vector>

namespace ContainerLoading
{
namespace Algorithms
{
using namespace ContainerLoading::Model;

class InterfaceConversions
{
  public:
    // Duplicate code in LoadingChecker::SelectItems. Is required for the current quick and dirty removal of vehicle
    // routing logic from the container loading module. A cleaner separation requires major rework in the container
    // loading submodule.
    static std::vector<Cuboid>
        SelectItems(const Collections::IdVector& nodeIds, const std::vector<Node>& nodes, bool reversedDirection);

    static std::vector<Group> NodesToGroup(const std::vector<Node>& nodes);
};

}
}