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

void animarBusqueda(sf::RenderWindow& window,
  const std::vector<IPathFinder::Paso>& pasos,
  const Graph& graph,
  const std::map<long long, Coordenada>& nodos,
  const std::map<long long, std::vector<Coordenada>>& caminos,
  double minLon, double maxLon, double minLat, double maxLat,
  int W, int H,
  long long inicio, long long destino,
  int colorAnimacion, std::vector<sf::Color>& colores,
  sf::View& view,
  const float ZOOM_FACTOR, const float MOVE_SPEED,
  int delay_ms) {
  sf::VertexArray animadas(sf::PrimitiveType::Lines, 0);
  bool saltarAnimacion = false;

  for (const auto& paso : pasos) {
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
        return;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::B)) {
        saltarAnimacion = true;
        break;
      }
    }

    if(saltarAnimacion) break;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) view.move({-MOVE_SPEED, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) view.move({MOVE_SPEED, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) view.move({0, -MOVE_SPEED});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) view.move({0, MOVE_SPEED});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q)) view.zoom(ZOOM_FACTOR);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E)) view.zoom(1.f / ZOOM_FACTOR);

    const auto& nodoA = graph.getNodes().at(paso.desde);
    const auto& nodoB = graph.getNodes().at(paso.hacia);

    sf::Vector2f p1 = normalizar({nodoA.lon, nodoA.lat}, minLon, maxLon, minLat, maxLat, W, H);
    sf::Vector2f p2 = normalizar({nodoB.lon, nodoB.lat}, minLon, maxLon, minLat, maxLat, W, H);

    animadas.append(sf::Vertex({p1, colores[colorAnimacion % colores.size()]}));
    animadas.append(sf::Vertex({p2, colores[colorAnimacion % colores.size()]}));

    window.clear(sf::Color::Black);
    window.setView(view);

    for (const auto& [_, puntos] : caminos) {
      sf::VertexArray v(sf::PrimitiveType::LineStrip, puntos.size());
      for (size_t i = 0; i < puntos.size(); ++i)
        v[i].position = normalizar(puntos[i], minLon, maxLon, minLat, maxLat, W, H),
        v[i].color = sf::Color(75, 75, 75);
      window.draw(v);
    }

    for (const auto& [id, coord] : nodos) {
      sf::Vector2f pos = normalizar(coord, minLon, maxLon, minLat, maxLat, W, H);
      sf::CircleShape punto(1.0f);
      if ((inicio != -1 && id == inicio) || (destino != -1 && id == destino)) {
        punto.setRadius(3.0f);
        punto.setFillColor(sf::Color::Magenta);
      } else {
        punto.setFillColor(sf::Color::Yellow);
      }
      punto.setOrigin({2.f, 2.f});
      punto.setPosition(pos);
      window.draw(punto);
    }

    window.draw(animadas);
    window.display();
    sf::sleep(sf::milliseconds(delay_ms));
  }
}

void animarRutaCorta(sf::RenderWindow& window,
  const std::vector<long long>& path,
  const Graph& graph,
  const std::map<long long, Coordenada>& nodos,
  const std::map<long long, std::vector<Coordenada>>& caminos,
  double minLon, double maxLon, double minLat, double maxLat,
  int W, int H,
  long long inicio, long long destino,
  int colorAnimacion, std::vector<sf::Color>& colores,
  int delay_ms) {
  sf::VertexArray rutaAnimada(sf::PrimitiveType::Lines, 0);

  for (size_t i = 1; i < path.size(); ++i) {
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
        return;
      }
    }

    const auto& nodoA = graph.getNodes().at(path[i - 1]);
    const auto& nodoB = graph.getNodes().at(path[i]);

    sf::Vector2f p1 = normalizar({nodoA.lon, nodoA.lat}, minLon, maxLon, minLat, maxLat, W, H);
    sf::Vector2f p2 = normalizar({nodoB.lon, nodoB.lat}, minLon, maxLon, minLat, maxLat, W, H);

    rutaAnimada.append(sf::Vertex({p1, colores[colorAnimacion % colores.size()]}));
    rutaAnimada.append(sf::Vertex({p2, colores[colorAnimacion % colores.size()]}));

    window.clear(sf::Color::Black);

    for (const auto& [_, puntos] : caminos) {
      sf::VertexArray v(sf::PrimitiveType::LineStrip, puntos.size());
      for (size_t i = 0; i < puntos.size(); ++i)
        v[i].position = normalizar(puntos[i], minLon, maxLon, minLat, maxLat, W, H),
        v[i].color = sf::Color(75, 75, 75);
      window.draw(v);
    }

    for (const auto& [id, coord] : nodos) {
      sf::Vector2f pos = normalizar(coord, minLon, maxLon, minLat, maxLat, W, H);
      sf::CircleShape punto(1.0f);
      if ((inicio != -1 && id == inicio) || (destino != -1 && id == destino)) {
        punto.setRadius(3.0f);
        punto.setFillColor(sf::Color::Magenta);
      } else {
        punto.setFillColor(sf::Color::Yellow);
      }
      punto.setOrigin({2.f, 2.f});
      punto.setPosition(pos);
      window.draw(punto);
    }

    window.draw(rutaAnimada);
    window.display();
    sf::sleep(sf::milliseconds(delay_ms));
  }
}
