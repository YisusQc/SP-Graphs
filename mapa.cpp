#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <optional>
#include "graph.hpp"
#include "utilities.hpp"
#include "algoritmos/unsa_algoritmos.hpp"

const float ZOOM_FACTOR = 1.02f;
const float MOVE_SPEED = 2.0f;

int main() {
  int mapaActual = 1;
  std::string basePath = "data/mapa" + std::to_string(mapaActual) + "/";

  for (int i = 1; i <= 5; i++)
    std::ofstream("data/mapa" + std::to_string(i) + "/rutas_cortas.csv", std::ios::trunc).close();

  const int W = 1100, H = 800;
  sf::RenderWindow window(sf::VideoMode({W, H}), "Ruta Mas Corta");
  sf::View view = window.getDefaultView();

  std::vector<sf::Color> colores = {
    sf::Color::Red, sf::Color::Green, sf::Color::Magenta,
    {255,136,0}, {136,0,255}, {0,136,136}, {170,0,170}
  };

  Graph graph;
  std::map<long long, Coordenada> nodos;
  std::map<long long, std::vector<Coordenada>> caminos;
  std::vector<std::vector<Coordenada>> rutas;
  double minLon, maxLon, minLat, maxLat;

  cargarNodos(basePath, nodos, minLon, maxLon, minLat, maxLat);
  cargarCaminos(basePath, caminos);
  graph.load(basePath + "nodes.csv", basePath + "edges.csv");

  long long inicio = -1, destino = -1;
  int colorAnimacion = 0;

  std::unique_ptr<IPathFinder> algoritmo = std::make_unique<Dijkstra>();

  while (window.isOpen()) {
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) window.close();

      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::N)) {
        view = window.getDefaultView();
        colorAnimacion = 0;
        mapaActual = (mapaActual % 5) + 1;
        basePath = "data/mapa" + std::to_string(mapaActual) + "/";
        std::cout << "Cambiando a mapa " << mapaActual << "\n";

        cargarNodos(basePath, nodos, minLon, maxLon, minLat, maxLat);
        cargarCaminos(basePath, caminos);
        rutas = cargarRutas(basePath);
        graph.load(basePath + "nodes.csv", basePath + "edges.csv");
        inicio = destino = -1;

      } else if (event->is<sf::Event::MouseButtonPressed>()) {
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
        std::cout << "Algoritmo: " << algoritmo->name() << "\n";
        std::cout << "Calculando ruta de " << inicio << " a " << destino << "\n";

        auto prevMap = algoritmo->findPath(graph, inicio, destino);
        auto path = graph.reconstruct_path(prevMap, inicio, destino);

        if (!path.empty()) {
          const auto& pasos = algoritmo->getPasosAnimados();
          sf::VertexArray animadas(sf::PrimitiveType::Lines, 0);

          bool saltarAnimacion = false;
          // Bucle de animacion de expansión
          for (const auto& paso : pasos) {

            while (std::optional event = window.pollEvent()) {
              if (event->is<sf::Event::Closed>()) {
                window.close();
                return 0;
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

            // Redibujar mapa base
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

            // Dibujar todos los pasos acumulados para la animación
            window.draw(animadas);
            window.display();
            sf::sleep(sf::milliseconds(5));
          }

          // Bucle de animacion de ruta encontrada
          saltarAnimacion = false;
          sf::VertexArray rutaAnimada(sf::PrimitiveType::Lines, 0);
          for (size_t i = 1; i < path.size(); ++i) {
            while (std::optional event = window.pollEvent()) {
              if (event->is<sf::Event::Closed>()) {
                window.close();
                return 0;
              }
            }

            if(saltarAnimacion) break;

            const auto& nodoA = graph.getNodes().at(path[i - 1]);
            const auto& nodoB = graph.getNodes().at(path[i]);

            sf::Vector2f p1 = normalizar({nodoA.lon, nodoA.lat}, minLon, maxLon, minLat, maxLat, W, H);
            sf::Vector2f p2 = normalizar({nodoB.lon, nodoB.lat}, minLon, maxLon, minLat, maxLat, W, H);

            rutaAnimada.append(sf::Vertex({p1, colores[colorAnimacion % colores.size()]}));
            rutaAnimada.append(sf::Vertex({p2, colores[colorAnimacion % colores.size()]}));

            window.clear(sf::Color::Black);

            // Redibujar mapa base
            for (const auto& [_, puntos] : caminos) {
              sf::VertexArray v(sf::PrimitiveType::LineStrip, puntos.size());
              for (size_t j = 0; j < puntos.size(); ++j)
                v[j].position = normalizar(puntos[j], minLon, maxLon, minLat, maxLat, W, H),
                v[j].color = sf::Color(75, 75, 75);
              window.draw(v);
            }

            // Redibujar nodos
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

            // Dibujar ruta animada parcial
            window.draw(rutaAnimada);
            window.display();
            sf::sleep(sf::milliseconds(50));
          }

          colorAnimacion++;
          graph.save_route(path, inicio, destino, rutaArchivo, graph.getNodes());
          rutas = cargarRutas(basePath);
          std::cout << "Ruta agregada con exito.\n";
        } else
          std::cout << "No se encontro ruta.\n";
        inicio = destino = -1;

      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C)) {
        std::ofstream(basePath + "rutas_cortas.csv", std::ios::trunc).close();
        rutas.clear();
        std::cout << "Rutas del mapa " << mapaActual << " liberadas.\n";
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) view.move({-MOVE_SPEED, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) view.move({MOVE_SPEED, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) view.move({0, -MOVE_SPEED});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) view.move({0, MOVE_SPEED});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q)) view.zoom(ZOOM_FACTOR);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E)) view.zoom(1.f / ZOOM_FACTOR);

    window.clear(sf::Color::Black);
    window.setView(view);

    for (const auto& [_, puntos] : caminos) {
      sf::VertexArray v(sf::PrimitiveType::LineStrip, puntos.size());
      for (size_t i = 0; i < puntos.size(); ++i)
        v[i].position = normalizar(puntos[i], minLon, maxLon, minLat, maxLat, W, H),
        v[i].color = sf::Color(75, 75, 75);
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

    window.display();
  }

  return 0;
}
