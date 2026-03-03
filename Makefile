CXX = g++
CXXFLAGS = -I. -I./algoritmos
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = mapa
SRC = $(wildcard *.cpp) \ $(wildcard algoritmos/**/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o algoritmos/*/*.o

