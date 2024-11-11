#!/bin/bash

g++ generator.cpp lodepng/lodepng.cpp -o convert -I lodepng -D TERM_HEIGHT=$(tput lines) -D TERM_WIDTH=$(tput cols)
