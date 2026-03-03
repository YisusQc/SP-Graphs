#pragma once
#include <string>
#include "graph.hpp"
#include "unsa/vector/vector.hpp"
#include "unsa/unordered_map/unordered_map.hpp"
class IPathFinder {
public:
  struct Paso { long long desde, hacia; };
  unsa::vector<Paso> pasosAnimados;
  
  virtual ~IPathFinder() = default;
  virtual std::string name() const = 0;
  virtual unsa::unordered_map<long long, long long> findPath(const Graph& graph, long long start, long long goal) = 0;
  const unsa::vector<Paso>& getPasosAnimados() const { return pasosAnimados; }
  int getIteraciones() const { return iteraciones; }

protected:
  int iteraciones = 0;
};

