#include "../IPathFinder.hpp"
#include "../algoritmos/AStar/AStar.hpp"
#include "../algoritmos/BFS/BFS.hpp"
#include "../algoritmos/BestFS/BestFS.hpp"
#include "../algoritmos/DFS/DFS.hpp"
#include "../algoritmos/Dijkstra/Dijkstra.hpp"
#include "../graph.hpp"
#include <algorithm>
#include <chrono>
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <unistd.h>
#include "../unsa/vector/vector.hpp"
#include "../unsa/unordered_map/unordered_map.hpp"

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")
#endif

long getMemoryUsageKB() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize / 1024;
    }
    return 0;
#else
    long rss = 0;
    std::ifstream statm("/proc/self/statm");
    if (statm) {
        long size, resident;
        statm >> size >> resident;
        rss = resident * sysconf(_SC_PAGESIZE) / 1024;
    }
    return rss;
#endif
}

constexpr double R = 6371000.0; // Radio Tierra (m)
double haversine(const Node &a, const Node &b) {
  auto toRad = [](double deg) { return deg * M_PI / 180.0; };
  double dlat = toRad(b.lat - a.lat);
  double dlon = toRad(b.lon - a.lon);
  double lat1 = toRad(a.lat), lat2 = toRad(b.lat);
  double h = sin(dlat / 2) * sin(dlat / 2) +
             cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
  return 2 * R * atan2(sqrt(h), sqrt(1 - h));
}

unsa::vector<long long>
reconstruct_path(const unsa::unordered_map<long long, long long> &prev,
                 long long start, long long goal) {
  unsa::vector<long long> path;
  long long at = goal;
  while (at != start) {
    if (prev.find(at) == prev.end())
      return {};
    path.push_back(at);
    at = prev.at(at);
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}

int main() {
  Graph graph;
  graph.load("nodes.csv", "edges.csv");

  const auto &nodos = graph.getNodes();
  unsa::vector<long long> ids;
  for (const auto &[id, _] : nodos)
    ids.push_back(id);

  if (ids.size() < 2) {
    std::cerr << "\u274c No hay suficientes nodos.\n";
    return 1;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, ids.size() - 1);
  long long start = ids[dis(gen)];
  long long goal = ids[dis(gen)];
  while (goal == start)
    goal = ids[dis(gen)];

  unsa::vector<IPathFinder *> algoritmos = {new BFS(), new DFS(), new Dijkstra(),
                                           new BestFs(), new AStar()};
  std::ofstream metricas("metricas.csv");
  metricas << "algoritmo,tiempo,longitud,memoria_kb,distancia_metros\n";

  std::ofstream rutas("rutas_cortas.csv");

  for (IPathFinder *alg : algoritmos) {
    auto t_start = std::chrono::high_resolution_clock::now();
    auto prev = alg->findPath(graph, start, goal);
    auto t_end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> dur = t_end - t_start;
    auto path = reconstruct_path(prev, start, goal);

    double total_dist = 0.0;
    for (size_t i = 1; i < path.size(); ++i)
      total_dist += haversine(nodos.at(path[i - 1]), nodos.at(path[i]));

    long memoria_kb = getMemoryUsageKB();

    metricas << alg->name() << "," << dur.count() << "," << path.size() << ","
             << memoria_kb << "," << total_dist << "\n";

    rutas << "# " << alg->name() << ",inicio:" << start << ",destino:" << goal
          << "\n";
    rutas << "id,lat,lon\n";
    for (auto id : path) {
      const auto &n = nodos.at(id);
      rutas << id << "," << n.lat << "," << n.lon << "\n";
    }
    rutas << "\n";

    delete alg; // ¡Importante!
  }

  std::cout << "Comparacion completada. Revisa 'metricas.csv' y "
               "'rutas_cortas.csv'.\n";
  return 0;
}
