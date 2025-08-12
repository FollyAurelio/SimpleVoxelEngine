UNAME_S = $(shell uname -s)
CXX = g++
CC = gcc
CXXFLAGS = -g
CXXFLAGS += -Ilib/glfw/include -Ilib/glad/include -Ilib -Wall
LDFLAGS = lib/glad/src/glad.o lib/glfw/src/libglfw3.a

# GLFW required frameworks on OSX
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa
endif

ifeq ($(UNAME_S), Linux)
	LDFLAGS += -ldl -lpthread
endif
SRC = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp) 
OBJ = $(SRC:.cpp=.o)
BIN = bin

all:dirs libs program

libs:
	cd lib/glfw && cmake . && make
	cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c
	#cd lib/freetype && cmake -B build -D FT_DISABLE_BROTLI=ON -D FT_DISABLE_BZIP2=ON -D FT_DISABLE_HARFBUZZ=ON -D FT_DISABLE_PNG=ON -D FT_DISABLE_ZLIB=ON && cd build && make
dirs:
	mkdir -p ./$(BIN)
program:$(OBJ)
	$(CXX) -o $(BIN)/main $^ $(LDFLAGS)
%.o:%.cpp %.h
	$(CXX) -o $@ -c $< $(CXXFLAGS)
run:program
	$(BIN)/main

clean:
	rm -rf $(BIN) $(OBJ)

