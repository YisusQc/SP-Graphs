#pragma once
#include "../../IPathFinder.hpp"

class AStar : public IPathFinder {
public:
  std::string name() const override { return "A*"; }
  std::unordered_map<long long, long long> findPath(const Graph& graph, long long start, long long goal) override;
};

