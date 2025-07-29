#include "Dijkstra.hpp"
#include <unordered_map>
#include <limits>
#include <algorithm>
#include "../../unsa/priority_queue/priority_queue.hpp"
#include "../../unsa/vector/vector.hpp"
#include "../../unsa/pair/pair.hpp"
#include "../../unsa/unordered_map/unordered_map.hpp"
unsa::unordered_map<long long, long long> Dijkstra::findPath(const Graph& graph, long long start, long long goal) {
    iteraciones = 0;
    pasosAnimados.clear();

    const auto& nodes = graph.getNodes();
    const auto& adj = graph.getGraph();

    unsa::unordered_map<long long, double> dist;
    unsa::unordered_map<long long, long long> prev;

    for (const auto& [id, _] : nodes)
        dist[id] = std::numeric_limits<double>::infinity();

    dist[start] = 0.0;

    using PQNode = unsa::pair<double, long long>;  // {distance, node}
    unsa::priority_queue<PQNode, unsa::vector<PQNode>, std::greater<>> pq;
    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top(); pq.pop();
        iteraciones++;

        if (currentDist > dist[u]) continue;
        if (u == goal) break;

        auto it = adj.find(u);
        if (it == adj.end()) continue;

        for (const auto& edge : it->second) {
            double alt = dist[u] + edge.distance;
            if (alt < dist[edge.target]) {
                dist[edge.target] = alt;
                prev[edge.target] = u;
                pasosAnimados.push_back({u, edge.target});
                pq.push({alt, edge.target});
            }
        }
    }

    return prev;
}

