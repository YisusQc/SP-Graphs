#pragma once
#include "../IPathFinder.hpp"

class DFS : public IPathFinder {
  std::string name() const override { return "DFS"; }
  std::unordered_map<long long, long long> findPath(const Graph& graph, long long start, long long goal) override;
};
