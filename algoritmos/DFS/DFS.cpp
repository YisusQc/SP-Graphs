#include "DFS.hpp"
#include <unordered_map>
#include <unordered_set>
#include "../../unsa/unsa.hpp"

std::unordered_map<long long, long long> DFS::findPath(const Graph& graph, long long start, long long goal) {
  pasosAnimados.clear();
  iteraciones = 0;

  const auto& adj = graph.getGraph();
  std::unordered_map<long long, long long> prev;
  std::unordered_set<long long> visited;
  unsa::Stack<long long> stk;

  stk.push(start);

  while (!stk.empty()) {
    long long current = stk.top();
    stk.pop();

    if (visited.find(current) != visited.end()) continue;
    visited.insert(current);
    iteraciones++;

    if (current == goal) break;

    auto it = adj.find(current);
    if (it != adj.end()) {
      for (const Edge& edge : it->second) {
        if (visited.find(edge.target) == visited.end()) {
          prev[edge.target] = current;
          pasosAnimados.push_back({current, edge.target});
          stk.push(edge.target);
        }
      }
    }
  }

  return prev;
}
