#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <optional> // NECESARIO para std::optional
#include "Graph.hpp"
#include "utilities.hpp"

int main() {
  int mapaActual = 1;
  std::string basePath = "data/mapa" + std::to_string(mapaActual) + "/";

  for (int i = 1; i <= 5; i++)
    std::ofstream("data/mapa" + std::to_string(i) + "/rutas_cortas.csv", std::ios::trunc).close();

  const int W = 1100, H = 800;
  sf::RenderWindow window(sf::VideoMode({W, H}), "Ruta Mas Corta");

  std::vector<sf::Color> colores = {
    sf::Color::Red, sf::Color::Green, sf::Color::Blue,
    {255,136,0}, {136,0,255}, {0,136,136}, {170,0,170}
  };

  Graph graph;
  std::map<long long, Coordenada> nodos;
  std::map<long long, std::vector<Coordenada>> caminos;
  std::vector<std::vector<Coordenada>> rutas;
  double minLon, maxLon, minLat, maxLat;

  cargarNodos(basePath, nodos, minLon, maxLon, minLat, maxLat);
  cargarCaminos(basePath, caminos);
  rutas = cargarRutas(basePath);
  graph.load(basePath + "nodes.csv", basePath + "edges.csv");

  long long inicio = -1, destino = -1;

  while (window.isOpen()) {
    sf::Event rawEvent;
    while (window.pollEvent(rawEvent)) {
      std::optional<sf::Event> event = rawEvent;

      if (event->type == sf::Event::Closed) window.close();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) window.close();

      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::N)) {
        mapaActual = (mapaActual % 5) + 1;
        basePath = "data/mapa" + std::to_string(mapaActual) + "/";
        std::cout << "Cambiando a mapa " << mapaActual << "\n";

        cargarNodos(basePath, nodos, minLon, maxLon, minLat, maxLat);
        cargarCaminos(basePath, caminos);
        rutas = cargarRutas(basePath);
        graph.load(basePath + "nodes.csv", basePath + "edges.csv");
        inicio = destino = -1;

      } else if (event->type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f clic = window.mapPixelToCoords(mousePos);
        long long nodo = nodoMasCercano(clic, W, H, 8.f, nodos, minLon, maxLon, minLat, maxLat);
        if (nodo != -1) {
          if (inicio == -1) { inicio = nodo; std::cout << "Inicio: " << inicio << '\n'; }
          else if (destino == -1 && nodo != inicio) {
            destino = nodo;
            std::cout << "Destino: " << destino << '\n';
          } else {
            inicio = nodo; destino = -1;
            std::cout << "Nuevo inicio: " << inicio << '\n';
          }
        }
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R) && inicio != -1 && destino != -1) {
        std::string rutaArchivo = basePath + "rutas_cortas.csv";
        std::cout << "Calculando ruta de " << inicio << " a " << destino << "\n";
        if (graph.compute_and_save_route(inicio, destino, rutaArchivo)) {
          rutas = cargarRutas(basePath);
          std::cout << "Ruta agregada con éxito.\n";
        } else
          std::cout << "No se encontró ruta.\n";
        inicio = destino = -1;

      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C)) {
        std::ofstream(basePath + "rutas_cortas.csv", std::ios::trunc).close();
        rutas.clear();
        std::cout << "Rutas del mapa " << mapaActual << " liberadas.\n";
      }
    }

    window.clear(sf::Color::Black);

    for (const auto& [_, puntos] : caminos) {
      sf::VertexArray v(sf::PrimitiveType::LineStrip, puntos.size());
      for (size_t i = 0; i < puntos.size(); ++i)
        v[i].position = normalizar(puntos[i], minLon, maxLon, minLat, maxLat, W, H),
        v[i].color = sf::Color(200, 200, 200);
      window.draw(v);
    }

    for (size_t i = 0; i < rutas.size(); ++i) {
      auto& ruta = rutas[i];
      sf::VertexArray r(sf::PrimitiveType::LineStrip, ruta.size());
      for (size_t j = 0; j < ruta.size(); ++j)
        r[j].position = normalizar(ruta[j], minLon, maxLon, minLat, maxLat, W, H),
        r[j].color = colores[i % colores.size()];
      window.draw(r);
    }

    for (const auto& [id, coord] : nodos) {
      sf::Vector2f pos = normalizar(coord, minLon, maxLon, minLat, maxLat, W, H);

      sf::CircleShape punto(1.5f);
      punto.setFillColor(sf::Color::Yellow);
      punto.setOrigin({2.f, 2.f});
      punto.setPosition(pos);

      window.draw(punto);
    }

    window.display();
  }

  return 0;
}