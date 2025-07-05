#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>
#include "utilities.hpp"

sf::Vector2f normalizar(Coordenada coord, double minLon, double maxLon, double minLat, double maxLat, int width, int height) {
  double x = (coord.first - minLon) / (maxLon - minLon) * width;
  double y = height - (coord.second - minLat) / (maxLat - minLat) * height;
  return {static_cast<float>(x), static_cast<float>(y)};
}

float distancia(const sf::Vector2f& a, const sf::Vector2f& b) {
  return std::hypot(a.x - b.x, a.y - b.y);
}

bool esEncabezadoRuta(const std::string& line) {
  return line.rfind("INICIO:", 0) == 0 || line == "id,lat,lon";
}

void cargarNodos(const std::string& basePath, std::map<long long, Coordenada>& nodos, double& minLon, double& maxLon, double& minLat, double& maxLat) {
  nodos.clear();
  std::ifstream file(basePath + "nodes.csv");
  std::string line; std::getline(file, line);

  minLon = minLat = std::numeric_limits<double>::max();
  maxLon = maxLat = std::numeric_limits<double>::lowest();

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    long long id; double lat, lon; char sep;
    ss >> id >> sep >> lat >> sep >> lon;
    nodos[id] = {lon, lat};
    minLon = std::min(minLon, lon);
    maxLon = std::max(maxLon, lon);
    minLat = std::min(minLat, lat);
    maxLat = std::max(maxLat, lat);
  }
}

void cargarCaminos(const std::string& basePath, std::map<long long, std::vector<Coordenada>>& caminos) {
  caminos.clear();
  std::ifstream file(basePath + "ways.csv");
  std::string line; std::getline(file, line);

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string id_str, lon_str, lat_str;
    std::getline(ss, id_str, ',');
    std::getline(ss, lon_str, ',');
    std::getline(ss, lat_str, ',');
    long long id = std::stoll(id_str);
    double lon = std::stod(lon_str);
    double lat = std::stod(lat_str);
    caminos[id].emplace_back(lon, lat);
  }
}

std::vector<std::vector<Coordenada>> cargarRutas(const std::string& basePath) {
  std::ifstream file(basePath + "rutas_cortas.csv");
  std::vector<std::vector<Coordenada>> rutas;
  std::vector<Coordenada> actual;
  std::string line;
  while (std::getline(file, line)) {
    if (line.empty() || esEncabezadoRuta(line)) {
      if (!actual.empty()) rutas.push_back(actual), actual.clear();
      continue;
    }
    std::stringstream ss(line);
    std::string id, lat_str, lon_str;
    std::getline(ss, id, ','); std::getline(ss, lat_str, ','); std::getline(ss, lon_str, ',');
    actual.emplace_back(std::stod(lon_str), std::stod(lat_str));
  }
  if (!actual.empty()) rutas.push_back(actual);
  return rutas;
}

long long nodoMasCercano(sf::Vector2f clic, int W, int H, float umbral, std::map<long long, Coordenada>& nodos, double& minLon, double& maxLon, double& minLat, double& maxLat) {
  long long mejor = -1;
  float mejorDist = umbral;
  for (auto& [id, coord] : nodos) {
    sf::Vector2f pos = normalizar(coord, minLon, maxLon, minLat, maxLat, W, H);
    float dist = distancia(clic, pos);
    if (dist < mejorDist) mejorDist = dist, mejor = id;
  }
  return mejor;
}
