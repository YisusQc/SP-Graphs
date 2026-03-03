#include "BestFS.hpp"
#include "../../unsa/priority_queue/priority_queue.hpp"
#include "../../unsa/vector/vector.hpp"
#include "../../unsa/pair/pair.hpp"
#include "../../unsa/unordered_map/unordered_map.hpp"
#include "../../unsa/math/math.hpp"
static double distancia(const Node& a, const Node& b) {
    double dx = a.lon - b.lon;
    double dy = a.lat - b.lat;
    return unsa::sqrt(dx * dx + dy * dy);
}

unsa::unordered_map<long long, long long> BestFs::findPath(const Graph& graph, long long start, long long goal) {
    pasosAnimados.clear();
    iteraciones = 0;
    const auto& nodes = graph.getNodes();
    const auto& adj = graph.getGraph();

    unsa::unordered_map<long long, bool> visited;
    unsa::unordered_map<long long, long long> prev;

    using PQNode = unsa::pair<double, long long>; // (heurística, nodo)
    unsa::priority_queue<PQNode, unsa::vector<PQNode>, std::greater<>> pq;

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

