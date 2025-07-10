CXX = g++
CXXFLAGS = -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = mapa
SRC = mapa.cpp graph.cpp utilities.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f mapa *.o
