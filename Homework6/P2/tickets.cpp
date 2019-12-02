/**
 * Copyright (c) 2019, HongtuXu
 * All rights reserved.
 *
 * @author HongtuXu
 * @date 2019-11-17
 */
#include "tickets.h"
#include <functional>

LotteryTicket::LotteryTicket() : m_numbers(), m_round(), hasClaimed() {}

LotteryTicket::LotteryTicket(const CustomSet<int> &numbers, int round)
    : m_numbers(numbers), m_round(round), hasClaimed() {}

LotteryTicket::~LotteryTicket() {}

const int LotteryTicket::getRound() const { return m_round; }

const int LotteryTicket::getCost() const { return m_cost; }

void LotteryTicket::setCost(const int &cost) { m_cost = cost; }

// Lotto6Ticket
Lotto6Ticket::Lotto6Ticket(const CustomSet<int> &numbers, int round)
    : LotteryTicket(numbers, round) {
    setCost(2 * getBinom(numbers.size(), 6));
}

Lotto6Ticket::~Lotto6Ticket() {}

const int Lotto6Ticket::getTicketType() const { return LOTTO6; }

const int Lotto6Ticket::claimPrize(const CustomSet<int> &prizeNumbers, int round) {
    if (round != getRound() || hasClaimed) return 0;
    const CustomSet<int> &numbers = getNumbers();
    hasClaimed = true;
    const int n = numbers.size();
    static const int PRIZE[] = {0, 0, 0, 5, 75, 4500, 2000000};
    if (n == 6) return PRIZE[(prizeNumbers & numbers).size()];
    const int a = (prizeNumbers & numbers).size();
    int ret = 0;
    for (int i = 3; i <= 6; i++) ret += getBinom(a, i) * getBinom(n - a, 6 - i) * PRIZE[i];
    return ret;
}

// Lotto7Ticket

Lotto7Ticket::Lotto7Ticket(const CustomSet<int> &numbers, int round)
    : LotteryTicket(numbers, round) {
    setCost(2 * getBinom(numbers.size(), 7));
}

Lotto7Ticket::~Lotto7Ticket() {}

const int Lotto7Ticket::getTicketType() const { return LOTTO7; }

const int Lotto7Ticket::claimPrize(const CustomSet<int> &prizeNumbers, int round) {
    if (round != getRound() || hasClaimed) return 0;
    const CustomSet<int> &numbers = getNumbers();
    hasClaimed = true;
    const int n = numbers.size();
    static const int PRIZE[] = {0, 0, 0, 0, 5, 75, 4500, 2000000};
    if (n == 7) return PRIZE[(prizeNumbers & numbers).size()];
    const int a = (prizeNumbers & numbers).size();
    int ret = 0;
    for (int i = 4; i <= 7; i++) ret += getBinom(a, i) * getBinom(n - a, 7 - i) * PRIZE[i];
    return ret;
}