#! /bin/sh.
#g++ -c Source.cpp
#g++ Source.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#./sfml-app
g++ main.o -o sfml-app -L<sfml-install-path>/lib -lsfml-graphics -lsfml-window -lsfml-system
