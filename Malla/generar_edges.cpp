#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "../unsa/vector/vector.hpp"
#include "../unsa/math/math.hpp"
#include "../unsa/pair/pair.hpp"
struct Nodo {
    long id;
    double lat;
    double lon;
};

double distancia(const Nodo& a, const Nodo& b) {
    return unsa::sqrt(unsa::pow(a.lat - b.lat, 2) + unsa::pow(a.lon - b.lon, 2));
}

int main() {
    std::ifstream entrada("nodes.csv");
    std::ofstream salida("edges.csv");
    std::string linea;
    std::getline(entrada, linea); // Skip header

    unsa::vector<Nodo> nodos;
    while (std::getline(entrada, linea)) {
        std::stringstream ss(linea);
        std::string id_str, lat_str, lon_str;
        std::getline(ss, id_str, ',');
        std::getline(ss, lat_str, ',');
        std::getline(ss, lon_str, ',');

        Nodo nodo = {
            std::stol(id_str),
            std::stod(lat_str),
            std::stod(lon_str)
        };
        nodos.push_back(nodo);
    }

    salida << "from,to,distance\n";

    // Conectar cada nodo con sus 3 más cercanos
    for (size_t i = 0; i < nodos.size(); ++i) {
        unsa::vector<unsa::pair<double, int>> distancias;

        for (size_t j = 0; j < nodos.size(); ++j) {
            if (i == j) continue;
            double d = distancia(nodos[i], nodos[j]);
            distancias.emplace_back(d, j);
        }

        std::sort(distancias.begin(), distancias.begin() + 10); // Ordena por distancia
        for (int k = 0; k < 3; ++k) {
            int idx = distancias[k].second;
            salida << nodos[i].id << "," << nodos[idx].id << "," << distancias[k].first << "\n";
        }

        if (i % 100000 == 0) std::cout << "Procesado " << i << " nodos\n";
    }

    std::cout << "Generado edges.csv\n";
    return 0;
}
