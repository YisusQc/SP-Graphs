#include "BFS.hpp"
#include <queue>
#include <unordered_set>
#include "../../graph.hpp"

std::vector<long long> BFSPathFinder::find_path(
    const Graph& graph,
    long long start,
    long long goal
) const{
    std::unordered_map<long long, long long> prev;
    std::unordered_set<long long> visited;
    std::queue<long long> q;

    q.push(start);
    visited.insert(start);

    const auto& adj = graph.getGraph();

    while (!q.empty()) {
        long long current = q.front();
        q.pop();

        if (current == goal) {
            return graph.reconstruct_path(prev, start, goal);
        }

        auto it = adj.find(current);
        if (it != adj.end()) {
            for (const Edge& edge : it->second) {
                if (visited.find(edge.target) == visited.end()) {
                    visited.insert(edge.target);
                    prev[edge.target] = current;
                    q.push(edge.target);
                }
            }
        }
    }

    // Si no hay camino
    return {};
}

