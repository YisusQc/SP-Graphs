#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "../graph.hpp"
#include "../utilities.hpp"

struct Nodo {
  long id;
  double lat;
  double lon;
};

Nodo generarNodo(long id_base, std::mt19937& rng, std::uniform_real_distribution<>& lat_dist, std::uniform_real_distribution<>& lon_dist) {
  return { id_base, lat_dist(rng), lon_dist(rng) };
}

int main() {
  const int N = 2000; // Objetivo 1 Millon
  const long id_inicio = 255000000;
  const std::string archivo = "nodes.csv";

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_real_distribution<> lat_dist(-16.4000, -16.3900);
  std::uniform_real_distribution<> lon_dist(-71.5400, -71.5300);

  std::ofstream salida(archivo);
  salida << "id,lat,lon\n";

  for (int i = 0; i < N; ++i) {
      Nodo nodo = generarNodo(id_inicio + i, rng, lat_dist, lon_dist);
      salida << nodo.id << "," << std::fixed << std::setprecision(6)
              << nodo.lat << "," << nodo.lon << "\n";
  }

  salida.close();
  std::cout << "Generado " << N << " nodos en '" << archivo << "'\n";


  Graph graph;
  std::map<long long, Coordenada> nodos;
  double minLon, maxLon, minLat, maxLat;
  graph.loadNodes("nodes.csv");
  cargarNodos("", nodos, minLon, maxLon, minLat, maxLat);

  // COMENTAR PARTE GRAFICA para pruebas de TRIANGULARIZACION con N mayor a 2k /*
  const int W = 1400, H = 900;
  sf::RenderWindow window(sf::VideoMode({W, H}), "Malla");

  while (window.isOpen()) {
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) window.close();
    }

    window.clear(sf::Color::Black);

    for (const auto& [id, coord] : nodos) {
      sf::Vector2f pos = normalizar(coord, minLon, maxLon, minLat, maxLat, W, H);
      sf::CircleShape punto(1.0f);
      punto.setRadius(1.0f);
      punto.setFillColor(sf::Color::Yellow);
      punto.setOrigin({2.f, 2.f});
      punto.setPosition(pos);

      window.draw(punto);
    }

    window.display();
  }
  // */

  return 0;
}