#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

using Coordenada = std::pair<double, double>;

sf::Vector2f normalizar(Coordenada coord, double minLon, double maxLon, double minLat, double maxLat, int width, int height);
float distancia(const sf::Vector2f& a, const sf::Vector2f& b);
bool esEncabezadoRuta(const std::string& line);

void cargarNodos(const std::string& basePath, std::map<long long, Coordenada>& nodos, double& minLon, double& maxLon, double& minLat, double& maxLat);
void cargarCaminos(const std::string& basePath, std::map<long long, std::vector<Coordenada>>& caminos);
std::vector<std::vector<Coordenada>> cargarRutas(const std::string& basePath);

long long nodoMasCercano(sf::Vector2f clic, int W, int H, float umbral, std::map<long long, Coordenada>& nodos, double& minLon, double& maxLon, double& minLat, double& maxLat);
