#include <random>
#include <iostream>
#include <functional>
#include <fstream>
#include <Windows.h>

int main() {
    int testCases;
    {
        std::ifstream in("cnt.txt");
        in >> testCases;
    }
    std::ofstream out("cnt.txt");
    out << testCases + 1;
    auto gen = std::bind(std::uniform_int_distribution<>(0, 6), std::mt19937(GetTickCount()));
    auto gen2 = std::bind(std::uniform_int_distribution<>(0, 25), std::mt19937(GetTickCount()));
    for (int i = 0; i < 1000; i++) {
        char c;
        switch (gen()) {
            case 0: {
                c = 'a';
                break;
            }
            case 1: {
                c = 'b';
                break;
            }
            case 2: {
                c = 'c';
                break;
            }
            case 3: {
                c = 'u';
                break;
            }
            case 4: {
                c = 'd';
                break;
            }
            case 5: {
                c = 'g';
                break;
            }
            case 6: {
                c = 'a' + gen2();
                break;
            }
        }
        std::cout << c << '\n';
    }
}