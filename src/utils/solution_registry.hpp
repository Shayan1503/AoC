#pragma once
#include "../solutions/solution.hpp"
#include <functional>
#include <map>
#include <tuple>

using SolutionKey = std::tuple<int, int, int>;
using SolutionFactory = std::function<std::unique_ptr<Solution>(int mode)>;

inline std::map<SolutionKey, SolutionFactory> &getSolutionRegistry() {
  static std::map<SolutionKey, SolutionFactory> registry;
  return registry;
}

inline void registerSolution(int year, int day, int part, SolutionFactory factory) {
  getSolutionRegistry()[{year, day, part}] = factory;
}

inline std::unique_ptr<Solution> makeSolution(int year, int day, int part, int mode) {
  auto &registry = getSolutionRegistry();
  auto it = registry.find({year, day, part});

  if (it != registry.end()) {
    return it->second(mode);
  }

  return nullptr;
}

inline std::map<int, std::map<int, std::vector<int>>> getAvailableSolutions() {
  auto &registry = getSolutionRegistry();
  std::map<int, std::map<int, std::vector<int>>> solutions_map = {};
  for (const auto &entry : registry) {
    const auto &[year, day, part] = entry.first;
    solutions_map[year][day].push_back(part);
  }

  return solutions_map;
}

#define REGISTER_SOLUTION(CLASS, YEAR, DAY, PART)                              \
  namespace {                                                                  \
  struct CLASS##Registrar {                                                    \
    CLASS##Registrar() {                                                       \
      registerSolution(YEAR, DAY, PART, [](int mode) {                         \
        return std::make_unique<CLASS>(mode);                                  \
      });                                                                      \
    }                                                                          \
  };                                                                           \
  static CLASS##Registrar global_##CLASS##Registrar;                           \
  }
