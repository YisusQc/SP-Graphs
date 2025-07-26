#include "graph.hpp"
#include <fstream>
#include <sstream>
#include "unsa/unsa.hpp"
#include <limits>
#include <algorithm>
#include <iostream>

void Graph::load(const std::string& nodes_file, const std::string& edges_file) {
  nodes.clear();
  graph.clear();

  std::ifstream file(nodes_file);
  std::string line; 
  std::getline(file, line);  // saltar header
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    long long id;
    double lat, lon;
    char sep;
    ss >> id >> sep >> lat >> sep >> lon;
    nodes[id] = {id, lat, lon};
  }

  std::ifstream edge_file(edges_file);
  std::getline(edge_file, line);  // saltar header
  while (std::getline(edge_file, line)) {
    std::stringstream ss(line);
    long long src, tgt;
    double dist;
    char sep;
    ss >> src >> sep >> tgt >> sep >> dist;
    graph[src].push_back({tgt, dist});
  }
}

void Graph::loadNodes(const std::string& nodes_file) {
  nodes.clear();
  graph.clear();

  std::ifstream file(nodes_file);
  std::string line; 
  std::getline(file, line);  // saltar header
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    long long id;
    double lat, lon;
    char sep;
    ss >> id >> sep >> lat >> sep >> lon;
    nodes[id] = {id, lat, lon};
  }
}

std::vector<long long> Graph::reconstruct_path(const std::unordered_map<long long, long long>& prev, long long start, long long goal) const{
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

void Graph::save_route(const std::vector<long long>& path, long long start, long long goal, const std::string& output_file, const std::unordered_map<long long, Node>& nodes) {
  std::ofstream file(output_file, std::ios::app);
  file << "INICIO:" << start << ",DESTINO:" << goal << "\n";
  file << "id,lat,lon\n";
  for (long long id : path) {
    const Node& n = nodes.at(id);
    file << id << "," << n.lat << "," << n.lon << "\n";
  }
  file << "\n";
}
