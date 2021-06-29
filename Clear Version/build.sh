#! /bin/sh.
g++ -c Source.cpp
g++ Source.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./sfml-app
