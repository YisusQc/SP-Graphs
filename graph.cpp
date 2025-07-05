#include "Graph.hpp"
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>

void Graph::load(const std::string& nodes_file, const std::string& edges_file) {
  nodes.clear();
  graph.clear();

  std::ifstream file(nodes_file);
  std::string line; std::getline(file, line);
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    long long id;
    double lat, lon;
    char sep;
    ss >> id >> sep >> lat >> sep >> lon;
    nodes[id] = {id, lat, lon};
  }

  std::ifstream edge_file(edges_file);
  std::getline(edge_file, line);
  while (std::getline(edge_file, line)) {
    std::stringstream ss(line);
    long long src, tgt;
    double dist;
    char sep;
    ss >> src >> sep >> tgt >> sep >> dist;
    graph[src].push_back({tgt, dist});
  }
}

std::unordered_map<long long, long long> Graph::dijkstra(long long start, long long goal) {
  std::unordered_map<long long, double> dist;
  std::unordered_map<long long, long long> prev;

  for (auto& [id, _] : nodes)
    dist[id] = std::numeric_limits<double>::infinity();
  dist[start] = 0.0;

  auto cmp = [&](long long a, long long b) { return dist[a] > dist[b]; };
  std::priority_queue<long long, std::vector<long long>, decltype(cmp)> pq(cmp);
  pq.push(start);

  while (!pq.empty()) {
    long long u = pq.top(); pq.pop();
    if (u == goal) break;
    for (auto& edge : graph[u]) {
      double alt = dist[u] + edge.distance;
      if (alt < dist[edge.target]) {
        dist[edge.target] = alt;
        prev[edge.target] = u;
        pq.push(edge.target);
      }
    }
  }
  return prev;
}

std::vector<long long> Graph::reconstruct_path(const std::unordered_map<long long, long long>& prev, long long start, long long goal) {
  std::vector<long long> path;
  long long at = goal;
  while (at != start) {
    path.push_back(at);
    if (prev.find(at) == prev.end()) return {};  // ruta no encontrada
    at = prev.at(at);
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}

bool Graph::compute_and_save_route(long long start, long long goal, const std::string& output_file) {
  auto prev = dijkstra(start, goal);
  auto path = reconstruct_path(prev, start, goal);
  if (path.empty()) return false;

  std::ofstream file(output_file, std::ios::app);
  file << "INICIO:" << start << ",DESTINO:" << goal << "\n";
  file << "id,lat,lon\n";
  for (long long id : path) {
    const Node& n = nodes[id];
    file << id << "," << n.lat << "," << n.lon << "\n";
  }
  file << "\n";
  return true;
}
