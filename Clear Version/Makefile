.PHONY: clean all
.DEFAULT_GOAL := all

CC=g++
CFLAGS=-Wall -Wpedantic -ggdb -std=c++11 -O0
BUILD_DIR=build

SRC = game/game.cpp
OBJ = $(BUILD_DIR)/engine.o


all: game
game: engine.o libs/engine/interface.h $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(OBJ) -I./libs -o "$(BUILD_DIR)/game"


engine.o: libs/engine/base.h libs/engine/interface.h
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/engine.o -c libs/engine/base.cpp


clean:
ifeq ($(OS),Windows_NT)
	del /q "$(BUILD_DIR)\*"
else
	@rm -f "$(BUILD_DIR)/*"
endif