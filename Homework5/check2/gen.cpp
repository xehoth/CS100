#include <iostream>
#include <unordered_set>
#include <string>
#include <ctime>

char get() {
    switch (rand() % 3) {
        case 0: {
            return '0' + rand() % 10;
            break;
        }
        case 1: {
            return 'a' + rand() % 26;
            break;
        }
        case 2: {
            return 'A' + rand() % 26;
            break;
        }
    }
    return '0';
}

std::string gen() {
    std::string s;
    int len = rand() % 5 + 1;
    len = rand() % len + 1;
    for (int i = 0; i < len; i++) s += get();
    return s;
}

int main() {
    char *t = new char;
    srand(time(0) ^ (long long)t);
    int m = rand() % 10 + 1, n = rand() % 10 + 1;
    int o = rand() % n;
    std::cout << n << ' ' << m << ' ' << o << '\n';
    for (int i = 0; i < n; i++) {
        std::unordered_set<std::string> s;
        while (s.size() < m) {
            s.insert(gen());
        }
        for (auto p : s) std::cout << p << ' ';
        std::cout << '\n';
    }
    delete t;
}