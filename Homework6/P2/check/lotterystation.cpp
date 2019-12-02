/**
 * Copyright (c) 2019, HongtuXu
 * All rights reserved.
 *
 * @author HongtuXu
 * @date 2019-11-17
 */
#include "lotterystation.h"

int randInt(int min, int max) {
    if (max < min) std::swap(max, min);
    return rand() % (max - min + 1) + min;
}

LotteryStation::LotteryStation() : m_round() {}

LotteryStation::~LotteryStation() {}

LotteryTicket *LotteryStation::buy(CustomSet<int> numbers, int tickettype) {
    if (tickettype == LOTTO6) {
        if (numbers.size() < 6) {
            std::cout << "Failed.\n";
            return nullptr;
        }
        auto check = [&]() {
            for (int i : numbers.getData())
                if (!(1 <= i && i <= 43)) return false;
            return true;
        };
        if (!check()) {
            std::cout << "Failed.\n";
            return nullptr;
        }
        LotteryTicket *ret = new Lotto6Ticket(numbers, m_round);
        std::cout << "Bought a Lotto 6 ticket for " << ret->getCost() << " Yuan at round "
                  << m_round << ".\n";
        return ret;
    }
    //
    if (tickettype == LOTTO7) {
        if (numbers.size() < 7) {
            std::cout << "Failed.\n";
            return nullptr;
        }
        auto check = [&]() {
            for (int i : numbers.getData())
                if (!(1 <= i && i <= 30)) return false;
            return true;
        };
        if (!check()) {
            std::cout << "Failed.\n";
            return nullptr;
        }
        LotteryTicket *ret = new Lotto7Ticket(numbers, m_round);
        std::cout << "Bought a Lotto 7 ticket for " << ret->getCost() << " Yuan at round "
                  << m_round << ".\n";
        return ret;
    }
    std::cout << "Failed.\n";
    return nullptr;
}

void LotteryStation::claimPrize(LotteryTicket *ticket) {
    int ret = 0;
    if (ticket && ticket->getTicketType() == LOTTO6) {
        ret = ticket->claimPrize(prize6, m_round);
    }
    if (ticket && ticket->getTicketType() == LOTTO7) {
        ret = ticket->claimPrize(prize7, m_round);
    }
    std::cout << "This ticket wins " << ret << " Yuan.\n";
}

void LotteryStation::newRound() {
    ++m_round;
    {
        CustomSet<int> tmp;
        while (tmp.size() != 7) tmp.add(randInt(1, 30));
        prize7 = tmp;
    }
    {
        CustomSet<int> tmp;
        while (tmp.size() != 6) tmp.add(randInt(1, 43));
        prize6 = tmp;
    }
}

const bool LotteryStation::setPrizeNumbers(CustomSet<int> numbers, int tickettype) {
    if (tickettype == LOTTO6) {
        if (numbers.size() != 6) return false;
        for (int i : numbers.getData())
            if (!(1 <= i && i <= 43)) return false;
        prize6 = numbers;
        return true;
    }
    if (tickettype == LOTTO7) {
        if (numbers.size() != 7) return false;
        for (int i : numbers.getData())
            if (!(1 <= i && i <= 30)) return false;
        prize7 = numbers;
        return true;
    }
    return false;
}