#include <ctime>
#include <random>
#include <iostream>
#include <functional>
#include <iomanip>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    auto gen = std::bind(std::uniform_real_distribution<>(), std::mt19937(time(0)));
    auto genI = std::bind(std::uniform_int_distribution<>(1, 5), std::mt19937(time(0)));
    double start = gen();  // gen();
    long long startL = (long long)(start * 10000) * 10;
    start = startL / 100000.0;
    long long incL;
    double inc;
    do {
        inc = gen();  // gen();
        incL = (long long)(inc * 10000) * 10;
    } while (incL == 0);

    inc = incL / 100000.0;
    int tot = genI();
    double end = (startL + incL * tot) / 100000.0;
    std::cout << std::fixed << start << ' ' << end << ' ' << inc << '\n';
    auto genD = std::bind(std::uniform_real_distribution<>(start, end), std::mt19937(time(0)));
    int n = genI();
    std::cout << n << '\n';
    auto genI2 = std::bind(std::uniform_int_distribution<>(1, tot), std::mt19937(time(0)));
    for (int i = 0; i < n; i++) {
        if (genI() & 1) {
            std::cout << genD() << '\n';
        } else {
            std::cout << start + inc * genI2() << '\n';
        }
    }
    return 0;
}