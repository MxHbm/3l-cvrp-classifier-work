#pragma once

#include "nlohmann/json.hpp"

using json = nlohmann::json;

#include "Model/Container.h"

#include <fstream>
#include <iomanip>


struct MIPSolverParams;
struct BranchAndCutParams;
struct ExtremePointParameters;
struct UserCutParams;
struct CPSolverParams;
struct LoadingProblemParams;
struct PackingParameters;

class InputParameters;

namespace ContainerLoading
{

void from_json(const json& j, LoadingProblemParams& params);
void to_json(json& j, const LoadingProblemParams& params);
}

namespace ContainerLoading
{
namespace Algorithms
{
/*
enum class Rotation;
enum class Fragility;

NLOHMANN_JSON_SERIALIZE_ENUM(Rotation, {{Rotation::None, "None"}, {Rotation::Yaw, "Yaw"}});

NLOHMANN_JSON_SERIALIZE_ENUM(Fragility, {{Fragility::None, "None"}, {Fragility::Fragile, "Fragile"}});
*/

void from_json(const json& j, InputParameters& inputParameters);
void to_json(json& j, const InputParameters& inputParameters);

void from_json(const json& j, CPSolverParams& params);
void to_json(json& j, const CPSolverParams& params);

/*
void from_json(const json& j, ExtremePointParameters& params);
void to_json(json& j, const ExtremePointParameters& params);
*/
}
}


namespace ContainerLoading
{
namespace Model
{

class Cuboid;
class Container;


NLOHMANN_JSON_SERIALIZE_ENUM(Rotation, {{Rotation::None, "None"}, {Rotation::Yaw, "Yaw"}});

NLOHMANN_JSON_SERIALIZE_ENUM(Fragility, {{Fragility::None, "None"}, {Fragility::Fragile, "Fragile"}});

void from_json(const json& j, Cuboid& item);
void to_json(json& j, const Cuboid& item);

void from_json(const json& j, Container& container);
void to_json(json& j, const Container& container);
}
}


/*
class Serializer
{
  public:
    template <class T>
    static void WriteToJson(const T& classToSerialize, std::string& folderPath, std::string& fileName)
    {
        std::ofstream ofs(folderPath + fileName + ".json");
        {
            if (!ofs.is_open())
            {
                throw std::runtime_error("File stream not open.");
            }

            json jsonFile = classToSerialize;
            ofs << std::setw(2) << jsonFile;
        }

        ofs.close();
    }
};
*/