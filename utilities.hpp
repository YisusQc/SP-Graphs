#pragma once
#include <SFML/Graphics.hpp>
#include "graph.hpp"
#include "IPathFinder.hpp"
#include <map>
#include <utility>

using Coordenada = std::pair<double, double>;

sf::Vector2f normalizar(Coordenada coord, double minLon, double maxLon, double minLat, double maxLat, int width, int height);
float distancia(const sf::Vector2f& a, const sf::Vector2f& b);
bool esEncabezadoRuta(const std::string& line);

void cargarNodos(const std::string& basePath, std::map<long long, Coordenada>& nodos, double& minLon, double& maxLon, double& minLat, double& maxLat);
void cargarCaminos(const std::string& basePath, std::map<long long, std::vector<Coordenada>>& caminos);
std::vector<std::vector<Coordenada>> cargarRutas(const std::string& basePath);
void cargarEtiquetas(const std::string& rutaArchivo, std::map<long long, std::string>& etiquetas);

long long nodoMasCercano(sf::Vector2f clic, int W, int H, float umbral, std::map<long long, Coordenada>& nodos, double& minLon, double& maxLon, double& minLat, double& maxLat);
double calcularDistancia(const Graph& graph, const std::vector<long long>& path);

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
  int delay_ms);

void animarRutaCorta(sf::RenderWindow& window,
  const std::vector<long long>& path,
  const Graph& graph,
  const std::map<long long, Coordenada>& nodos,
  const std::map<long long, std::vector<Coordenada>>& caminos,
  double minLon, double maxLon, double minLat, double maxLat,
  int W, int H,
  long long inicio, long long destino,
  int colorAnimacion, std::vector<sf::Color>& colores,
  sf::View& view,
  const float ZOOM_FACTOR, const float MOVE_SPEED,
  int delay_ms);

