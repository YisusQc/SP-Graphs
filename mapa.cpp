#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <optional>
#include <cmath>
#include "graph.hpp"
#include "utilities.hpp"
#include "algoritmos/unsa_algoritmos.hpp"
#include "algoritmos/BFS/BFS.hpp"

const float ZOOM_FACTOR = 1.02f;
const float MOVE_SPEED = 2.0f;

int main() {
  int mapaActual = 1;
  std::string basePath = "data/mapa" + std::to_string(mapaActual) + "/";

  for (int i = 1; i <= 5; i++)
    std::ofstream("data/mapa" + std::to_string(i) + "/rutas_cortas.csv", std::ios::trunc).close();

  sf::Font font;
  if (!font.openFromFile("fonts/arial.ttf")) { std::cerr << "Error al cargar la fuente\n"; }

  const int W = 1400, H = 900;
  sf::RenderWindow window(sf::VideoMode({W, H}), "Ruta Mas Corta");
  sf::View view = window.getDefaultView();

  std::vector<sf::Color> colores = {sf::Color::Red, sf::Color::Green, sf::Color::Magenta, {255,136,0}, {136,0,255}, {0,136,136}, {170,0,170}};
  std::vector<std::string> titulosMapa = {"Arequipa - Cercado", "Mariano Melgar - Plaza Umachiri", "Paucarpata baja", "Yura viejo", "Cerro Colorado - Fundo Cabrerias"};

  Graph graph;
  std::map<long long, Coordenada> nodos;
  std::map<long long, std::vector<Coordenada>> caminos;
  std::vector<std::vector<Coordenada>> rutas;
  std::vector<std::map<long long, std::string>> etiquetasPorMapa(5);
  double minLon, maxLon, minLat, maxLat;

  cargarNodos(basePath, nodos, minLon, maxLon, minLat, maxLat);
  cargarCaminos(basePath, caminos);
  cargarEtiquetas("data/mapa" + std::to_string(mapaActual) + "/etiquetas.csv", etiquetasPorMapa[mapaActual - 1]);
  graph.load(basePath + "nodes.csv", basePath + "edges.csv");

  long long inicio = -1, destino = -1;
  int algoritmoActual = 0;
  int colorAnimacion = 0;
  bool mostrarEtiquetas = true;
  bool mostrarEtiquetaPresionado = false;
  bool avanzarMapaPresionado = false;
  bool retrocederMapaPresionado = false;
  bool limpiarRutasPresionado = false;
  bool algoritmoPresionado = false;

  std::vector<std::unique_ptr<IPathFinder>> algoritmos;
  algoritmos.emplace_back(std::make_unique<Dijkstra>());
  algoritmos.emplace_back(std::make_unique<BFSPathFinder>());
  algoritmos.emplace_back(std::make_unique<BestFs>());
  algoritmos.emplace_back(std::make_unique<AStar>());

  while (window.isOpen()) {
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) window.close();

      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::L) && !mostrarEtiquetaPresionado) {
        if (mostrarEtiquetas) {
          std::cout << "Ocultando etiquetas" << "\n";
          mostrarEtiquetas = !mostrarEtiquetas;
        } else {
          std::cout << "Mostrar etiquetas" << "\n";
          mostrarEtiquetas = !mostrarEtiquetas;
        }
        mostrarEtiquetaPresionado = !mostrarEtiquetaPresionado;
      }

      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::N) && !avanzarMapaPresionado) {
        view = window.getDefaultView();
        colorAnimacion = 0;
        mapaActual = (mapaActual % 5) + 1;
        etiquetasPorMapa[mapaActual - 1].clear();
        basePath = "data/mapa" + std::to_string(mapaActual) + "/";
        std::cout << "Cambiando a mapa " << mapaActual << "\n";

        cargarNodos(basePath, nodos, minLon, maxLon, minLat, maxLat);
        cargarCaminos(basePath, caminos);
        rutas = cargarRutas(basePath);
        cargarEtiquetas("data/mapa" + std::to_string(mapaActual) + "/etiquetas.csv", etiquetasPorMapa[mapaActual - 1]);
        graph.load(basePath + "nodes.csv", basePath + "edges.csv");
        inicio = destino = -1;
        avanzarMapaPresionado = !avanzarMapaPresionado;

      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::P) && !retrocederMapaPresionado) {
        view = window.getDefaultView();
        colorAnimacion = 0;
        mapaActual = (mapaActual == 1) ? 5 : mapaActual - 1;
        etiquetasPorMapa[mapaActual - 1].clear();
        basePath = "data/mapa" + std::to_string(mapaActual) + "/";
        std::cout << "Cambiando a mapa " << mapaActual << "\n";

        cargarNodos(basePath, nodos, minLon, maxLon, minLat, maxLat);
        cargarCaminos(basePath, caminos);
        rutas = cargarRutas(basePath);
        cargarEtiquetas("data/mapa" + std::to_string(mapaActual) + "/etiquetas.csv", etiquetasPorMapa[mapaActual - 1]);
        graph.load(basePath + "nodes.csv", basePath + "edges.csv");
        inicio = destino = -1;
        retrocederMapaPresionado = !retrocederMapaPresionado;

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
        auto& algoritmo = algoritmos[algoritmoActual];
        std::cout << "Algoritmo: " << algoritmo->name() << "\n";
        std::cout << "Calculando ruta de " << inicio << " a " << destino << "\n";

        auto prevMap = algoritmo->findPath(graph, inicio, destino);
        auto path = graph.reconstruct_path(prevMap, inicio, destino);
        double distanciaTotal = calcularDistancia(graph, path);

        if (!path.empty()) {
          animarBusqueda(window, algoritmo->getPasosAnimados(), graph, nodos, caminos, minLon, maxLon, minLat, maxLat, W, H, inicio, destino, colorAnimacion, colores, view, ZOOM_FACTOR, MOVE_SPEED);

          std::cout << "Iteraciones: " << algoritmo->getIteraciones() << "\n";
          double km = distanciaTotal / 1000.0;
          km = std::floor(km * 100) / 100;
          std::cout << "Distancia de ruta encontrada: " << distanciaTotal << " metros (" << km << "km)\n";

          animarRutaCorta(window, path, graph, nodos, caminos, minLon, maxLon, minLat, maxLat, W, H, inicio, destino, colorAnimacion, colores);

          colorAnimacion++;
          graph.save_route(path, inicio, destino, rutaArchivo, graph.getNodes());
          rutas = cargarRutas(basePath);
          std::cout << "Ruta agregada con exito.\n";
        } else
          std::cout << "No se encontro ruta.\n";
        inicio = destino = -1;

      } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::M) && !algoritmoPresionado) {
        algoritmoActual = (algoritmoActual + 1) % algoritmos.size();
        std::cout << "Algoritmo cambiado a: " << algoritmos[algoritmoActual]->name() << "\n";
        algoritmoPresionado = true;

      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C) && !limpiarRutasPresionado) {
        std::ofstream(basePath + "rutas_cortas.csv", std::ios::trunc).close();
        rutas.clear();
        std::cout << "Rutas del mapa " << mapaActual << " liberadas.\n";
        limpiarRutasPresionado = !limpiarRutasPresionado;
      }
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::L))
      mostrarEtiquetaPresionado = !mostrarEtiquetaPresionado;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::N))
      avanzarMapaPresionado = !avanzarMapaPresionado;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::P))
      retrocederMapaPresionado = !retrocederMapaPresionado;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::M))
      algoritmoPresionado = false;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::C))
      limpiarRutasPresionado = !limpiarRutasPresionado;

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

      if (mostrarEtiquetas) {
        auto& etiquetas = etiquetasPorMapa[mapaActual - 1];
        auto it = etiquetas.find(id);
        if (it != etiquetas.end()) {
          sf::Text label(font);
          label.setCharacterSize(11);
          label.setString(it->second);
          label.setFillColor(sf::Color::White);
          label.setPosition(pos + sf::Vector2f(5.f, -12.f));
          window.draw(label);
        }
      }

      auto& etiquetas = etiquetasPorMapa[mapaActual - 1];
      bool esInicioODestino = (inicio != -1 && id == inicio) || (destino != -1 && id == destino);
      bool esEtiquetado = etiquetas.find(id) != etiquetas.end();

      if (esInicioODestino) {
        punto.setRadius(5.0f);
        punto.setFillColor(sf::Color::Magenta);
      } else if (mostrarEtiquetas && esEtiquetado) {
        punto.setRadius(3.0f);
        punto.setFillColor(sf::Color::Cyan);
      } else {
        punto.setFillColor(sf::Color::Yellow);
      }
      punto.setOrigin({2.f, 2.f});
      punto.setPosition(pos);

      window.draw(punto);
    }

    sf::Text titulo(font);
    titulo.setCharacterSize(16);
    titulo.setString(titulosMapa[mapaActual - 1]);
    titulo.setFillColor(sf::Color::White);
    titulo.setStyle(sf::Text::Bold);
    titulo.setPosition({8.f, 8.f});
    window.draw(titulo);

    sf::RectangleShape cajaTitulo({10.f + (titulosMapa[mapaActual - 1]).size() * 8.5f + 10.f, 30.f});
    cajaTitulo.setPosition({3.f, 3.f});
    cajaTitulo.setFillColor(sf::Color::Transparent);
    cajaTitulo.setOutlineThickness(3.0f);
    cajaTitulo.setOutlineColor(sf::Color::White);
    window.draw(cajaTitulo);

    window.display();
  }

  return 0;
}
