#pragma once
#include "graph.hpp"

class IPathFinder {
public:
  struct Paso { long long desde, hacia; };
  std::vector<Paso> pasosAnimados;
  
  virtual ~IPathFinder() = default;
  virtual std::string name() const = 0;
  virtual std::unordered_map<long long, long long> findPath(const Graph& graph, long long start, long long goal) = 0;
  const std::vector<Paso>& getPasosAnimados() const { return pasosAnimados; }
  int getIteraciones() const { return iteraciones; }

protected:
  int iteraciones = 0;
};

