#include "BFS.hpp"
#include <queue>
#include <unordered_set>

std::unordered_map<long long, long long> BFS::findPath(const Graph& graph, long long start, long long goal) {
    pasosAnimados.clear();
    iteraciones = 0;
    std::unordered_map<long long, long long> prev;
    std::unordered_set<long long> visited;
    std::queue<long long> q;

    q.push(start);
    visited.insert(start);

    const auto& adj = graph.getGraph();

    while (!q.empty()) {
        long long current = q.front();
        q.pop();
        iteraciones++;

        if (current == goal)
            break;

        auto it = adj.find(current);
        if (it != adj.end()) {
            for (const Edge& edge : it->second) {
                if (visited.find(edge.target) == visited.end()) {
                    visited.insert(edge.target);
                    prev[edge.target] = current;
                    pasosAnimados.push_back({current, edge.target});
                    q.push(edge.target);
                }
            }
        }
    }

    return prev;
}
