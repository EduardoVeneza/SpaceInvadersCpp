#!/bin/bash

g++ src/main.cpp src/Spaceship.cpp src/game.cpp src/laser.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11