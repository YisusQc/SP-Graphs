#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct Node {
  long long id;
  double lat;
  double lon;
};

struct Edge {
  long long target;
  double distance;
};

class Graph {
private:
  std::unordered_map<long long, Node> nodes;
  std::unordered_map<long long, std::vector<Edge>> graph;

public:
  void load(const std::string& nodes_file, const std::string& edges_file);
  std::vector<long long> reconstruct_path(const std::unordered_map<long long, long long>& prev, long long start, long long goal);
  void save_route(const std::vector<long long>& path, long long start, long long goal, const std::string& output_file, const std::unordered_map<long long, Node>& nodes);

  const std::unordered_map<long long, Node>& getNodes() const { return nodes; }
  const std::unordered_map<long long, std::vector<Edge>>& getGraph() const { return graph; }
};
