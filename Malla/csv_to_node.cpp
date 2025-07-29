#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <tuple>
#include <vector>
#include "../unsa/set/set.hpp"
#include "../unsa/vector/vector.hpp"
#include "../unsa/pair/pair.hpp"
int main() {
    std::ifstream fin("nodes.csv");
    std::ofstream fout("graph.node");
    std::string line;
    std::getline(fin, line); // saltar encabezado

    unsa::set<unsa::pair<double, double>> coords_vistas;
    unsa::vector<std::tuple<long long, double, double>> nodos;

    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        long long id;
        double lat, lon;
        char sep;
        ss >> id >> sep >> lat >> sep >> lon;

        if (!coords_vistas.count({lat, lon})) {
            coords_vistas.insert({lat, lon});
            nodos.emplace_back(id, lat, lon);
        }
    }

    fout << nodos.size() << " 2 0 0\n";
    for (size_t i = 0; i < nodos.size(); ++i) {
        auto [id, lat, lon] = nodos[i];
        fout << i + 1 << " " << lon << " " << lat << "\n"; // lon x, lat y
    }

    std::cout << "✔ graph.node generado sin duplicados (" << nodos.size() << " nodos).\n";
    return 0;
}

