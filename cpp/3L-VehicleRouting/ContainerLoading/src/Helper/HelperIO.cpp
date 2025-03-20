#include "Helper/HelperIO.h"

#include "CommonBasics/Helper/ModelServices.h"
#include "Helper/Serialization.h"
#include "Model/Instance.h"
#include "Model/Node.h"
#include "Model/Vehicle.h"

#include <map>

namespace ContainerLoading
{
namespace Helper
{
using json = nlohmann::json;

Instance HelperIO::ParseInstanceJson(std::ifstream& ifs)
{
    nlohmann::json jf = nlohmann::json::parse(ifs);

    std::string name = jf["Name"];

    const auto& vehiclesJson = jf["Vehicles"];

    int dimensionFactor = 1;
    std::vector<Vehicle> vehicles;
    for (size_t v = 0; v < vehiclesJson.size(); ++v)
    {
        const auto& vehicle = vehiclesJson[v];

        Container container = Container(vehicle.at("Length").get<int>() * dimensionFactor,
                                        vehicle.at("Width").get<int>() * dimensionFactor,
                                        vehicle.at("Height").get<int>() * dimensionFactor,
                                        vehicle.at("Capacity").get<int>());

        container.Volume = container.Dx * container.Dy * container.Dz;

        vehicles.emplace_back(v, std::vector<Container>({container}));
    }

    Container& container = vehicles.front().Containers.front();

    const auto& nodesJson = jf["Nodes"];
    std::vector<Node> nodes;
    int idItem = 0;
    for (const auto& nodeJson: nodesJson)
    {
        std::vector<Cuboid> items;
        double totalVolume = 0.0;
        double totalArea = 0.0;
        for (const auto& itemJson: nodeJson["Items"])
        {
            int quantity = itemJson["Quantity"];

            for (int d = 0; d < quantity; ++d)
            {
                items.emplace_back(idItem,
                                   idItem,
                                   itemJson.at("Length").get<int>() * dimensionFactor,
                                   itemJson.at("Width").get<int>() * dimensionFactor,
                                   itemJson.at("Height").get<int>() * dimensionFactor,
                                   true,
                                   itemJson.at("Fragility").get<Fragility>(),
                                   0,//itemJson.at("Volume").get<int>(),
                                   itemJson.at("Weight").get<double>());

                items.back().Volume = items.back().Dx * items.back().Dy * items.back().Dz;

                totalVolume += items.back().Volume;
                totalArea += items.back().Dx * items.back().Dy;

                idItem++;
            }
        }

        for (auto& item: items)
        {
            item.EnableHorizontalRotation = item.Dx <= container.Dy && item.Dy <= container.Dx;
        }

        nodes.emplace_back(nodeJson["Customer ID"],
                           nodeJson["Customer ID"],
                           nodeJson["x"],
                           nodeJson["y"],
                           nodeJson["Demanded Mass"],
                           totalVolume,
                           totalArea,
                           items);
    }

    return {name, vehicles, nodes};
}

ContainerLoading::Algorithms::InputParameters HelperIO::ReadInputParameters(std::string& parameterFilePath)
{
    std::ifstream inputStream(parameterFilePath);
    nlohmann::json jsonParameters;
    inputStream >> jsonParameters;

    return jsonParameters.get<ContainerLoading::Algorithms::InputParameters>();
}

std::vector<Route> HelperIO::ParseSolutionJson(std::ifstream& ifs)
{
    nlohmann::json jf = nlohmann::json::parse(ifs);

    const auto& routesJson = jf["Routes"];

    std::vector<Route> routes;

    for (const auto& routeJson: routesJson)
    {
        int id = routeJson["Id"];
        const auto& nodes = routeJson["Nodes"];

        Collections::IdVector sequence;
        for (const auto& node: nodes)
        {
            const auto& nodeId = node["ID"];
            sequence.push_back(nodeId);
        }

        routes.emplace_back(id, sequence);
    }

    return routes;
}

}
}