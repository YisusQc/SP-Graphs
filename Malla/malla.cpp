#include <iostream>
#include <fstream>
#include <unordered_set>
#include <random>

struct CoordenadaHash {
    size_t operator()(const std::pair<double, double>& p) const {
        return std::hash<double>()(p.first) ^ std::hash<double>()(p.second);
    }
};

int main() {
    const int N = 10000;
    std::unordered_set<std::pair<double, double>, CoordenadaHash> coords;

    std::ofstream out("nodes.csv");
    out << "id,lat,lon\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distLat(-16.41, -16.38);
    std::uniform_real_distribution<> distLon(-71.53, -71.50);

    long long id = 1;
    while (coords.size() < N) {
        double lat = distLat(gen);
        double lon = distLon(gen);
        auto p = std::make_pair(lon, lat);
        if (coords.insert(p).second) {
            out << id++ << "," << lat << "," << lon << "\n";
        }
    }

    out.close();
    std::cout << "Generados " << N << " nodos únicos en 'nodes.csv'\n";
    return 0;
}

