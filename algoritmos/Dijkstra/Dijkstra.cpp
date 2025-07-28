#include "Dijkstra.hpp"
#include <unordered_map>
#include "../unsa/unsa.hpp"
#include <limits>
#include <algorithm>

std::unordered_map<long long, long long> Dijkstra::findPath(const Graph& graph, long long start, long long goal) {
  iteraciones = 0;
  pasosAnimados.clear();
  const auto& nodes = graph.getNodes();
  const auto& adj = graph.getGraph();

  std::unordered_map<long long, double> dist;
  std::unordered_map<long long, long long> prev;

  for (const auto& [id, _] : nodes)
    dist[id] = std::numeric_limits<double>::infinity();
  dist[start] = 0.0;

  using PQNode = std::pair<double, long long>;
  unsa::PriorityQueue<PQNode, std::greater<>> pq;
  pq.push({0.0, start});

  while (!pq.empty()) {
    auto [d_u, u] = pq.top(); pq.pop();
    iteraciones++;
    if (d_u > dist[u]) continue;
    if (u == goal) break;

    if (adj.find(u) == adj.end()) continue;

    for (const auto& edge : adj.at(u)) {
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
