#!/bin/bash

g++ src/main.cpp src/alien.cpp src/Spaceship.cpp src/game.cpp src/laser.cpp src/block.cpp src/obstacle.cpp src/mysteryShip.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11