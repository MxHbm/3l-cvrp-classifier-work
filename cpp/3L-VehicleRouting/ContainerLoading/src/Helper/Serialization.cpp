#include "Helper/Serialization.h"

#include "Algorithms/CPSolverParameters.h"
#include "Model/Container.h"
#include "ProblemParameters.h"

#include "Algorithms/BCRoutingParams.h"

namespace ContainerLoading
{

void from_json(const json& j, LoadingProblemParams& params)
{
    j.at("ProblemVariant").get_to(params.Variant);
    j.at("SupportArea").get_to(params.SupportArea);
}

void to_json(json& j, const LoadingProblemParams& params)
{
    j = json{{"ProblemVariant", params.Variant}, {"SupportArea", params.SupportArea}};
}

NLOHMANN_JSON_SERIALIZE_ENUM(LoadingProblemParams::VariantType,
    {{LoadingProblemParams::VariantType::None, "None"},
     {LoadingProblemParams::VariantType::AllConstraints, "AllConstraints"},
     {LoadingProblemParams::VariantType::NoFragility, "NoFragility"},
     {LoadingProblemParams::VariantType::NoSupport, "NoSupport"},
     {LoadingProblemParams::VariantType::NoLifo, "NoLifo"},
     {LoadingProblemParams::VariantType::LoadingOnly, "LoadingOnly"},
     {LoadingProblemParams::VariantType::VolumeWeightApproximation,
      "VolumeWeightApproximation"},
     {LoadingProblemParams::VariantType::Volume, "Volume"},
     {LoadingProblemParams::VariantType::Weight, "Weight"}});

}

namespace ContainerLoading
{

namespace Algorithms
{

void from_json(const json& j, CPSolverParams& params)
{
    j.at("EnableCumulativeDimensions").get_to(params.EnableCumulativeDimensions);
    j.at("EnableNoOverlap2DFloor").get_to(params.EnableNoOverlap2DFloor);
    j.at("LogFlag").get_to(params.LogFlag);
    j.at("Threads").get_to(params.Threads);
    j.at("Seed").get_to(params.Seed);
}

void to_json(json& j, const CPSolverParams& params)
{
    j = json{{"EnableCumulativeDimensions", params.EnableCumulativeDimensions},
             {"EnableNoOverlap2DFloor", params.EnableNoOverlap2DFloor},
             {"LogFlag", params.LogFlag},
             {"Threads", params.Threads},
             {"Seed", params.Seed}};
}

void from_json(const json& j, InputParameters& inputParameters)
{
    j.at("LoadingProblemParams").get_to(inputParameters.ContainerLoading.LoadingProblem);
    j.at("CPSolverParams").get_to(inputParameters.ContainerLoading.CPSolver);
}

void to_json(json& j, const InputParameters& inputParameters)
{
    j = json{{"LoadingProblemParams", inputParameters.ContainerLoading.LoadingProblem},
             {"CPSolverParams", inputParameters.ContainerLoading.CPSolver}};
}

/*
NLOHMANN_JSON_SERIALIZE_ENUM(LoadingProblemParams::VariantType,
    {{LoadingProblemParams::VariantType::None, "None"},
     {LoadingProblemParams::VariantType::AllConstraints, "AllConstraints"},
     {LoadingProblemParams::VariantType::NoFragility, "NoFragility"},
     {LoadingProblemParams::VariantType::NoSupport, "NoSupport"},
     {LoadingProblemParams::VariantType::NoLifo, "NoLifo"},
     {LoadingProblemParams::VariantType::LoadingOnly, "LoadingOnly"},
     {LoadingProblemParams::VariantType::VolumeWeightApproximation,
      "VolumeWeightApproximation"},
     {LoadingProblemParams::VariantType::Volume, "Volume"},
     {LoadingProblemParams::VariantType::Weight, "Weight"}});

*/

}
}


namespace ContainerLoading
{
namespace Model
{

void from_json(const json& j, Cuboid& item)
{
    j.at("X").get_to(item.X);
    j.at("Y").get_to(item.Y);
    j.at("Z").get_to(item.Z);
    j.at("Dx").get_to(item.Dx);
    j.at("Dy").get_to(item.Dy);
    j.at("Dz").get_to(item.Dz);
    j.at("Weight").get_to(item.Weight);
    j.at("EnableHorizontalRotation").get_to(item.EnableHorizontalRotation);
    j.at("Fragility").get_to(item.Fragility);
    j.at("Rotated").get_to(item.Rotated);
}

void to_json(json& j, const Cuboid& item)
{
    j = json{
        {"X", item.X},
        {"Y", item.Y},
        {"Z", item.Z},
        {"Dx", item.Dx},
        {"Dy", item.Dy},
        {"Dz", item.Dz},
        {"Weight", item.Weight},
        {"EnableHorizontalRotation", item.EnableHorizontalRotation},
        {"Fragility", item.Fragility},
        {"Rotated", item.Rotated},
    };
}

void from_json(const json& j, Container& container)
{
    j.at("Dx").get_to(container.Dx);
    j.at("Dy").get_to(container.Dy);
    j.at("Dz").get_to(container.Dz);
    j.at("WeightLimit").get_to(container.WeightLimit);
}

void to_json(json& j, const Container& container)
{
    j = json{
        {"Dx", container.Dx},
        {"Dy", container.Dy},
        {"Dz", container.Dz},
        {"WeightLimit", container.WeightLimit},
    };
}

}
}

/*

enum class CallbackElement
{
    // Integer
    None,
    IntegerSolutions,
    DetermineRoutes,
    CheckRoutes,
    IntegerRoutes,
    SingleCustomer,
    MinNumVehicles,
    Disconnected,
    Connected,
    SingleVehicle,
    MinVehApproxInf,
    RoutePrechecked,
    RoutePrecheckedNot,
    CustCombiInf,
    CustCombiInfNot,
    HeuristicFeas,
    HeuristicInf,
    CPCheck,
    ExactLimitFeas,
    ExactLimitInf,
    ExactLimitUnk,
    TwoPathInequality,
    TwoPathInequalityNot,
    RegularPathInequality,
    RegularPathInequalityNot,
    TailPathInequality,
    ExactFeas,
    ExactInf,
    ExactInvalid,
    ReverseSequence,
    RevHeurFeas,
    RevExactFeas,
    RevExactInf,
    InfeasibleTailPathInequality,
    // Fractional
    FractionalSolutions,
    AddFracSolCuts,
    BuildGraph,
    // Heuristic
    SPHeuristic
};


NLOHMANN_JSON_SERIALIZE_ENUM(CallbackElement,
                             {{CallbackElement::None, "None"},
                              {CallbackElement::IntegerSolutions, "IntegerSolutions"},
                              {CallbackElement::DetermineRoutes, "DetermineRoutes"},
                              {CallbackElement::IntegerRoutes, "IntegerRoutes"},
                              {CallbackElement::CheckRoutes, "CheckRoutes"},
                              {CallbackElement::Disconnected, "DisconnectedRoutes"},
                              {CallbackElement::Connected, "ConnectedRoutes"},
                              {CallbackElement::SingleCustomer, "SingleCustRoutes"},
                              {CallbackElement::MinNumVehicles, "MinNumVeh"},
                              {CallbackElement::SingleVehicle, "SingleVehicle"},
                              {CallbackElement::MinVehApproxInf, "MinVehApproxInf"},
                              {CallbackElement::RoutePrechecked, "RoutePrechecked"},
                              {CallbackElement::RoutePrecheckedNot, "RoutePrecheckedNot"},
                              {CallbackElement::CustCombiInf, "CustCombiInfeasible"},
                              {CallbackElement::CustCombiInfNot, "CustCombiInfNot"},
                              {CallbackElement::HeuristicFeas, "HeuristicFeas"},
                              {CallbackElement::HeuristicInf, "HeuristicInf"},
                              {CallbackElement::CPCheck, "CPCheck"},
                              {CallbackElement::TwoPathInequality, "TwoPath"},
                              {CallbackElement::TwoPathInequalityNot, "TwoPathNot"},
                              {CallbackElement::RegularPathInequality, "RegPath"},
                              {CallbackElement::RegularPathInequalityNot, "RegPathNot"},
                              {CallbackElement::TailPathInequality, "TailPath"},
                              {CallbackElement::ExactLimitFeas, "ExactLimitFeas"},
                              {CallbackElement::ExactLimitInf, "ExactLimitInf"},
                              {CallbackElement::ExactLimitUnk, "ExactLimitUnk"},
                              {CallbackElement::ExactFeas, "ExactFeas"},
                              {CallbackElement::ExactInf, "ExactInf"},
                              {CallbackElement::ExactInvalid, "ExactInvalid"},
                              {CallbackElement::ReverseSequence, "RevSeq"},
                              {CallbackElement::RevHeurFeas, "RevHeurFeas"},
                              {CallbackElement::RevExactFeas, "RevExactFeas"},
                              {CallbackElement::RevExactInf, "RevInf"},
                              {CallbackElement::FractionalSolutions, "CheckFracSols"},
                              {CallbackElement::AddFracSolCuts, "AddFracSolCuts"},
                              {CallbackElement::BuildGraph, "BuildGraph"},
                              {CallbackElement::InfeasibleTailPathInequality, "InfTailPath"},
                              {CallbackElement::SPHeuristic, "SPHeur"}});*/