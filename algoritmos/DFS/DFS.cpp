#include "DFS.hpp"
#include "../../unsa/stack/stack.hpp"
#include "../../unsa/unordered_map/unordered_map.hpp"
#include "../../unsa/unordered_set/unordered_set.hpp"
unsa::unordered_map<long long, long long> DFS::findPath(const Graph& graph, long long start, long long goal) {
  pasosAnimados.clear();
  iteraciones = 0;

  const auto& adj = graph.getGraph();
  unsa::unordered_map<long long, long long> prev;
  unsa::unordered_set visited;
  unsa::Stack<long long> stk;

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
