#!/bin/bash
g++ -g main.cpp tickets.cpp lotterystation.cpp -o main -std=c++11 -D_DEBUG -Wall -Wextra -fsanitize=address