#include "lotterystation.h"
#include <fstream>
#include <random>
#include <functional>

template <typename T>
CustomSet<int> genSet(T &gen, int size) {
    CustomSet<int> ret;
    while (ret.size() != size) ret.add(gen());
    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::ifstream in("1.in");
    int seed, round, mode;
    in >> seed >> round >> mode;
    srand(seed);
    auto gen1 = std::bind(std::uniform_int_distribution<>(1, 43), std::mt19937(seed));
    auto gen2 = std::bind(std::uniform_int_distribution<>(1, 30), std::mt19937(seed));
    auto gen = std::bind(std::uniform_int_distribution<>(), std::mt19937(seed));
    LotteryStation station;
    station.setPrizeNumbers(genSet(gen1, 6), LOTTO6);
    station.setPrizeNumbers(genSet(gen2, 7), LOTTO7);
    for (int i = 0; i < round; i++) {
        int sz = gen() % 7 + 6;
        LotteryTicket *p = station.buy(genSet(gen1, sz), LOTTO6);
        station.claimPrize(p);
        delete p;
        p = station.buy(genSet(gen2, sz), LOTTO7);
        station.claimPrize(p);
        delete p;
    }
    if (!mode) return 0;
    if (station.buy({}, 0)) {
        std::cout << "Wrong Answer on buy with error type" << std::endl;
    }
    std::flush(std::cout);
    std::vector<std::vector<LotteryTicket *> > data;
    for (int i = 0; i < round; i++) {
        station.newRound();
        std::vector<LotteryTicket *> tickets;
        int tk = gen() % 20 + 1;

        while (tk--) {
            int sz;
            switch (gen() % 4) {
                case 0: {
                    sz = 6;
                    tickets.push_back(station.buy(genSet(gen1, sz), LOTTO6));
                    break;
                }
                case 1: {
                    sz = 7;
                    tickets.push_back(station.buy(genSet(gen2, sz), LOTTO7));
                    break;
                }
                default: {
                    sz = gen() % 15 + 1;
                    switch (gen() % 4) {
                        case 0: {
                            tickets.push_back(station.buy(genSet(gen1, sz), LOTTO6));
                            break;
                        }
                        case 1: {
                            tickets.push_back(station.buy(genSet(gen2, sz), LOTTO7));
                            break;
                        }
                        case 2: {
                            tickets.push_back(station.buy(genSet(gen, sz), LOTTO6));
                            break;
                        }
                        case 3: {
                            tickets.push_back(station.buy(genSet(gen, sz), LOTTO7));
                            break;
                        }
                    }
                    break;
                }
            }
        }
        data.push_back(tickets);
        for (auto p : tickets) {
            station.claimPrize(p);
        }

        station.claimPrize(nullptr);
        if (i > 0) {
            for (auto p : data[gen() % i]) {
                station.claimPrize(p);
            }
        }
        if (station.setPrizeNumbers({}, LOTTO6)) {
            std::cout << "Wrong Answer on set prize" << std::endl;
        }
        if (station.setPrizeNumbers(genSet(gen, 6), LOTTO6)) {
            std::cout << "Wrong Answer on set prize" << std::endl;
        }
        if (station.setPrizeNumbers(genSet(gen, 7), LOTTO7)) {
            std::cout << "Wrong Answer on set prize" << std::endl;
        }
        if (!station.setPrizeNumbers(genSet(gen1, 6), LOTTO6)) {
            std::cout << "Wrong Answer on set prize" << std::endl;
        }
        if (!station.setPrizeNumbers(genSet(gen2, 7), LOTTO7)) {
            std::cout << "Wrong Answer on set prize" << std::endl;
        }
        if (station.buy(genSet(gen1, 6), 2)) {
            std::cout << "Wrong Answer on buy with error type" << std::endl;
        }
        for (auto p : tickets) {
            station.claimPrize(p);
        }
        station.claimPrize(nullptr);
        if (i > 0) {
            for (auto p : data[gen() % i]) {
                station.claimPrize(p);
            }
        }
    }
    for (auto &vec : data) {
        for (auto p : vec) {
            delete p;
        }
    }
}