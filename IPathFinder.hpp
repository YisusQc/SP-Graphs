#pragma once
#include <unordered_map>
#include <string>
#include "graph.hpp"

class IPathFinder {
public:
  virtual ~IPathFinder() = default;
  virtual std::string name() const = 0;
  virtual std::unordered_map<long long, long long> findPath(const Graph& graph, long long start, long long goal) = 0;
};
