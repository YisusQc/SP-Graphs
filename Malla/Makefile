CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# Archivos fuente
SRC_DIR = .
GRAPH_SRC = ../graph.cpp
ALGOS = ../algoritmos/BFS/BFS.cpp \
        ../algoritmos/DFS/DFS.cpp \
        ../algoritmos/Dijkstra/Dijkstra.cpp \
        ../algoritmos/BestFS/BestFs.cpp \
        ../algoritmos/AStar/AStar.cpp

# Binaries
BIN_NODOS = generar_nodos
BIN_NODE = csv_to_node
BIN_EDGE = edge_to_csv
BIN_MAIN = main_batch

all: $(BIN_NODOS) $(BIN_NODE) $(BIN_EDGE) $(BIN_MAIN)

$(BIN_NODOS): $(SRC_DIR)/malla.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_NODE): $(SRC_DIR)/csv_to_node.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_EDGE): $(SRC_DIR)/edge_to_csv.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_MAIN): $(SRC_DIR)/main_batch.cpp $(GRAPH_SRC) $(ALGOS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: all
	./generar_nodos
	./csv_to_node
	triangle -e graph.node
	./edge_to_csv
	./main_batch

clean:
	rm -f $(BIN_NODOS) $(BIN_NODE) $(BIN_EDGE) $(BIN_MAIN)
	rm -f *.node *.ele *.edge
	rm -f nodes.csv edges.csv rutas_cortas.csv metricas.csv
