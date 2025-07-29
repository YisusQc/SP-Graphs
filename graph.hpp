#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "unsa/vector/vector.hpp"
#include "unsa/unordered_map/unordered_map.hpp"
struct Node {
    long long id;
    double lat, lon;
};

struct Edge {
    long long target;
    double distance;
};

class Graph {
public:
    void load(const std::string& nodes_file, const std::string& edges_file);
    unsa::vector<long long> findPathDijkstra(long long start, long long goal);
    void save_route(const unsa::vector<long long>& path, long long start, long long goal, const std::string& output_file, const unsa::unordered_map<long long, Node>& nodes);
    const unsa::unordered_map<long long, Node>& getNodes() const { return nodes; }
    const unsa::unordered_map<long long, unsa::vector<Edge>>& getGraph() const { return graph; }

    unsa::vector<long long> reconstruct_path(const unsa::unordered_map<long long, long long>& prev, long long start, long long goal) const;
private:
    unsa::unordered_map<long long, Node> nodes;
    unsa::unordered_map<long long, unsa::vector<Edge>> graph;
};
