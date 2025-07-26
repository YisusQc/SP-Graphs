#include "AStar.hpp"
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>

static double distancia(const Node& a, const Node& b) {
    double dx = a.lon - b.lon;
    double dy = a.lat - b.lat;
    return std::sqrt(dx * dx + dy * dy);
}

std::unordered_map<long long, long long> AStar::findPath(const Graph& graph, long long start, long long goal) {
    pasosAnimados.clear();
    const auto& nodes = graph.getNodes();
    const auto& adj = graph.getGraph();

    std::unordered_map<long long, double> g;       // Costo acumulado desde el inicio
    std::unordered_map<long long, double> f;       // f(n) = g(n) + h(n)
    std::unordered_map<long long, long long> prev; // Camino previo
    std::unordered_map<long long, bool> visited;

    using PQNode = std::pair<double, long long>; // (f(n), nodo)
    std::priority_queue<PQNode, std::vector<PQNode>, std::greater<>> pq;

    g[start] = 0.0;
    f[start] = distancia(nodes.at(start), nodes.at(goal));
    pq.push({f[start], start});

    while (!pq.empty()) {
        auto [_, current] = pq.top(); pq.pop();

        if (visited[current]) continue;
        visited[current] = true;

        if (current == goal) break;

        if (adj.find(current) == adj.end()) continue;

        for (const auto& edge : adj.at(current)) {
            long long neighbor = edge.target;
            double tentative_g = g[current] + edge.distance;

            if (!g.count(neighbor) || tentative_g < g[neighbor]) {
                prev[neighbor] = current;
                g[neighbor] = tentative_g;
                f[neighbor] = tentative_g + distancia(nodes.at(neighbor), nodes.at(goal));
                pq.push({f[neighbor], neighbor});
                pasosAnimados.push_back({current, neighbor});
            }
        }
    }

    return prev;
}
