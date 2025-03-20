#pragma once

#include "Model/Container.h"

#include <utility>
#include <vector>

namespace ContainerLoading
{
namespace Model
{
using namespace ContainerLoading::Model;

class Vehicle
{
  public:
    int InternId = 0;
    double Volume = 0.0;
    std::vector<Container> Containers;

    Vehicle() = default;
    Vehicle(int id, std::vector<Container> containers) : InternId(id), Containers(std::move(containers)) {}
};

}
}