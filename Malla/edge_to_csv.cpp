#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "../unsa/vector/vector.hpp"
#include "../unsa/vector/vector.tpp"
int main() {
    std::ifstream fin_node("nodes.csv");
    std::ifstream fin_edge("graph.1.edge");
    std::ofstream fout("edges.csv");

    std::string line;
    std::getline(fin_node, line); // saltar encabezado

    // Guardar IDs reales en orden
    unsa::vector<long long> ids;
    while (std::getline(fin_node, line)) {
        std::stringstream ss(line);
        long long id;
        double lat, lon;
        char sep;
        ss >> id >> sep >> lat >> sep >> lon;
        ids.push_back(id);
    }

    std::getline(fin_edge, line); // saltar encabezado
    fout << "source,target\n";

    while (std::getline(fin_edge, line)) {
        std::stringstream ss(line);
        int idx, from, to;
        ss >> idx >> from >> to;

        if (from > 0 && to > 0 && from <= ids.size() && to <= ids.size()) {
            fout << ids[from - 1] << "," << ids[to - 1] << "\n";
        }
    }

    std::cout << "edges.csv generado con " << (ids.size()) << " nodos.\n";
    return 0;
}

