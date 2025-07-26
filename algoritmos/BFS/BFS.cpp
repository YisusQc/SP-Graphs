#include "BFS.hpp"
#include <queue>
#include <unordered_set>

std::unordered_map<long long, long long> BFSPathFinder::findPath(
    const Graph& graph,
    long long start,
    long long goal
) {
    pasosAnimados.clear();  // Limpiar pasos anteriores
    std::unordered_map<long long, long long> prev;
    std::unordered_set<long long> visited;
    std::queue<long long> q;

    q.push(start);
    visited.insert(start);

    const auto& adj = graph.getGraph();

    while (!q.empty()) {
        long long current = q.front();
        q.pop();

        if (current == goal)
            break;

        auto it = adj.find(current);
        if (it != adj.end()) {
            for (const Edge& edge : it->second) {
                if (visited.find(edge.target) == visited.end()) {
                    visited.insert(edge.target);
                    prev[edge.target] = current;
                    pasosAnimados.push_back({current, edge.target}); // Para animación
                    q.push(edge.target);
                }
            }
        }
    }

    return prev;
}
