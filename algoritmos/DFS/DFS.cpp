#include "DFS.hpp"
#include <stack>
#include <unordered_set>

std::unordered_map<long long, long long> DFS::findPath(const Graph& graph, long long start, long long goal) {
  pasosAnimados.clear();
  iteraciones = 0;

  const auto& adj = graph.getGraph();
  std::unordered_map<long long, long long> prev;
  std::unordered_set<long long> visited;
  std::stack<long long> stk;

  stk.push(start);

  while (!stk.empty()) {
    long long current = stk.top();
    stk.pop();

    if (visited.contains(current)) continue;
    visited.insert(current);
    iteraciones++;

    if (current == goal) break;

    auto it = adj.find(current);
    if (it != adj.end()) {
      for (const Edge& edge : it->second) {
        if (!visited.contains(edge.target)) {
          prev[edge.target] = current;
          pasosAnimados.push_back({current, edge.target});
          stk.push(edge.target);
        }
      }
    }
  }

  return prev;
}

