#include "BFS.hpp"
#include "../../unsa/queue/queue.hpp"
#include "../../unsa/unordered_map/unordered_map.hpp"
#include "../../unsa/unordered_set/unordered_set.hpp"
unsa::unordered_map<long long, long long> BFS::findPath(const Graph& graph, long long start, long long goal) {
    pasosAnimados.clear();
    iteraciones = 0;
    unsa::unordered_map<long long, long long> prev;
    unsa::unordered_set visited;
    unsa::queue<long long> q;

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
                if (!visited.contains(edge.target)) {
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

