#include "BestFS.hpp"
#include "../unsa/unsa.hpp"
#include <unordered_map>
#include <cmath>
#include <limits>

static double distancia(const Node& a, const Node& b) {
    double dx = a.lon - b.lon;
    double dy = a.lat - b.lat;
    return std::sqrt(dx * dx + dy * dy);
}

std::unordered_map<long long, long long> BestFs::findPath(const Graph& graph, long long start, long long goal) {
    pasosAnimados.clear();
    iteraciones = 0;
    const auto& nodes = graph.getNodes();
    const auto& adj = graph.getGraph();

    std::unordered_map<long long, bool> visited;
    std::unordered_map<long long, long long> prev;

    using PQNode = std::pair<double, long long>; // (heurística, nodo)
    unsa::PriorityQueue<PQNode, std::greater<>> pq;

    pq.push({distancia(nodes.at(start), nodes.at(goal)), start});

    while (!pq.empty()) {
        auto [_, u] = pq.top(); pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        iteraciones++;

        if (u == goal) break;

        if (adj.find(u) == adj.end()) continue;

        for (const auto& edge : adj.at(u)) {
            if (!visited[edge.target]) {
                prev[edge.target] = u;
                pasosAnimados.push_back({u, edge.target});
                double h = distancia(nodes.at(edge.target), nodes.at(goal));
                pq.push({h, edge.target});
            }
        }
    }

    return prev;
}
