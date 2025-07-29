#pragma once
#include "../../IPathFinder.hpp"
#include "../../graph.hpp"
#include "../../unsa/unordered_map/unordered_map.hpp"
class Dijkstra : public IPathFinder {
public:
  std::string name() const override { return "Dijkstra"; }
  unsa::unordered_map<long long, long long> findPath(const Graph& graph, long long start, long long goal) override;
};
