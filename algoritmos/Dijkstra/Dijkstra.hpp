#pragma once
#include "../IPathFinder.hpp"
#include "graph.hpp"

class Dijkstra : public IPathFinder {
public:
  std::string name() const override { return "Dijkstra"; }
  std::unordered_map<long long, long long> findPath(const Graph& graph, long long start, long long goal) override;
};
