cmake_minimum_required(VERSION 3.30)
project(mapa LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

find_package(SFML CONFIG QUIET COMPONENTS Graphics Window System)

if(NOT TARGET SFML::Graphics)
  string(ASCII 27 Esc)
  message(FATAL_ERROR "${Esc}[1;31m[->] No se encontró 'SFML 3'${Esc}[0m")
endif()

add_executable(${PROJECT_NAME}
  mapa.cpp
  utilities.cpp
  graph.cpp
  algoritmos/AStar/Astar.cpp
  algoritmos/BestFS/BestFS.cpp
  algoritmos/BFS/BFS.cpp
  algoritmos/DFS/DFS.cpp
  algoritmos/Dijkstra/Dijkstra.cpp
)

target_link_libraries(${PROJECT_NAME}
  SFML::Graphics
  SFML::Window
  SFML::System
)

