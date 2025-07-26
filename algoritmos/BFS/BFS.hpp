#pragma once
#include "../../IPathFinder.hpp"
#include <vector>
#include "../../graph.hpp"

class BFSPathFinder : public IPathFinder {
public:
    std::vector<long long> find_path(
        const Graph& graph,
        long long start,
        long long goal
    ) const;
};
