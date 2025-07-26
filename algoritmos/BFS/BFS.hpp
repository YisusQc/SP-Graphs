#pragma once
#include "../../IPathFinder.hpp"
#include <unordered_map>
#include <string>

class BFSPathFinder : public IPathFinder {
public:
    std::string name() const override {
        return "BFS";
    }

    std::unordered_map<long long, long long> findPath(
        const Graph& graph,
        long long start,
        long long goal
    ) override;
};

