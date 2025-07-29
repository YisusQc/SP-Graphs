#pragma once
#include "../../IPathFinder.hpp"
#include <unordered_map>
#include <string>
#include "../../unsa/unordered_map/unordered_map.hpp"
class BFS : public IPathFinder {
public:
    std::string name() const override { return "BFS"; }
    unsa::unordered_map<long long, long long> findPath(const Graph& graph, long long start, long long goal) override;
};

