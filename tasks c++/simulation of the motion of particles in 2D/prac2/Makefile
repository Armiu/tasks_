CXX       := g++
CXX_FLAGS := -Wall -Wextra
INCLUDES  := -Iinclude

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   := `fltk-config --ldflags`
EXECUTABLE  := my

SOURCES := $(SRC)/graphics.cpp $(SRC)/system.cpp $(SRC)/lightparticle.cpp $(SRC)/heavyparticle.cpp $(SRC)/particle.cpp $(SRC)/main.cpp

all: clean
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -o $(BIN)/$(EXECUTABLE) $(SOURCES) $(LIBRARIES)

run: all
	clear
	./$(BIN)/$(EXECUTABLE)

clean:
	-rm $(BIN)/*
