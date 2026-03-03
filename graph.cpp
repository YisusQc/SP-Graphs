#include "graph.hpp"
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iostream>
#include "unsa/set/set.hpp"
#include "unsa/vector/vector.hpp"
#include "unsa/pair/pair.hpp"
#include "unsa/unordered_map/unordered_map.hpp"
void Graph::load(const std::string& nodes_file, const std::string& edges_file) {
    nodes.clear();
    graph.clear();

    std::ifstream file(nodes_file);
    std::string line;
    std::getline(file, line);
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

unsa::vector<long long> Graph::reconstruct_path(const unsa::unordered_map<long long, long long>& prev, long long start, long long goal) const {
    unsa::vector<long long> path;
    long long at = goal;
    while (at != start) {
        if (prev.find(at) == prev.end()) return {};
        path.push_back(at);
        at = prev.at(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

void Graph::save_route(const unsa::vector<long long>& path, long long start, long long goal, const std::string& output_file, const unsa::unordered_map<long long, Node>& nodes) {
    std::ofstream file(output_file, std::ios::app);
    file << "INICIO:" << start << ",DESTINO:" << goal << "\n";
    file << "id,lat,lon\n";
    for (long long id : path) {
        const Node& n = nodes.at(id);
        file << id << "," << n.lat << "," << n.lon << "\n";
    }
    file << "\n";
}

unsa::vector<long long> Graph::findPathDijkstra(long long start, long long goal) {
    unsa::unordered_map<long long, double> dist;
    unsa::unordered_map<long long, long long> prev;
    unsa::set<unsa::pair<double, long long>> pq;

    for (const auto& [id, _] : nodes) dist[id] = std::numeric_limits<double>::infinity();

    dist[start] = 0.0;
    pq.insert({0.0, start});

    while (!pq.empty()) {
        auto [current_dist, u] = *pq.begin();
        pq.erase(pq.begin());

        if (u == goal) break;

        for (const Edge& edge : graph[u]) {
            long long v = edge.target;
            double weight = edge.distance;
            double new_dist = current_dist + weight;

            if (new_dist < dist[v]) {
                pq.erase({dist[v], v});
                dist[v] = new_dist;
                prev[v] = u;
                pq.insert({new_dist, v});
            }
        }
    }

    return reconstruct_path(prev, start, goal);
}

