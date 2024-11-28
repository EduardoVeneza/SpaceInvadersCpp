#!/bin/bash

g++ src/main.cpp src/alien.cpp src/Spaceship.cpp src/game.cpp src/laser.cpp src/block.cpp src/obstacle.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11