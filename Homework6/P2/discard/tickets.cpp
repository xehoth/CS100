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

inline int getPrize6(int cnt) {
    if (cnt == 3) return 5;
    if (cnt == 4) return 75;
    if (cnt == 5) return 4500;
    if (cnt == 6) return 2000000;
    return 0;
}

const int Lotto6Ticket::claimPrize(const CustomSet<int> &prizeNumbers, int round) {
    if (round != getRound() || hasClaimed) return 0;
    const CustomSet<int> &numbers = getNumbers();
    const int n = numbers.size();
    if (n == 6) return getPrize6((prizeNumbers & numbers).size());
    int ret = 0;
    std::vector<int> data = numbers.getData();
    std::vector<int> choose;
    std::vector<bool> vis(n + 1);
    std::function<void(int)> dfs = [&](int now) {
        if (choose.size() > 6) return;
        if (now == n) {
            if (choose.size() != 6) return;
            ret += getPrize6((CustomSet<int>(choose.data(), 6) & prizeNumbers).size());
            return;
        }
        vis[now] = true;
        choose.push_back(data[now]);
        dfs(now + 1);
        choose.pop_back();
        vis[now] = false;
        dfs(now + 1);
    };
    dfs(0);
    hasClaimed = true;
    return ret;
}

// Lotto7Ticket

Lotto7Ticket::Lotto7Ticket(const CustomSet<int> &numbers, int round)
    : LotteryTicket(numbers, round) {
    setCost(2 * getBinom(numbers.size(), 7));
}

Lotto7Ticket::~Lotto7Ticket() {}

const int Lotto7Ticket::getTicketType() const { return LOTTO7; }

inline int getPrize7(int cnt) {
    if (cnt == 4) return 5;
    if (cnt == 5) return 75;
    if (cnt == 6) return 4500;
    if (cnt == 7) return 2000000;
    return 0;
}

const int Lotto7Ticket::claimPrize(const CustomSet<int> &prizeNumbers, int round) {
    if (round != getRound() || hasClaimed) return 0;
    const CustomSet<int> &numbers = getNumbers();
    const int n = numbers.size();
    if (n == 7) return getPrize7((prizeNumbers & numbers).size());
    int ret = 0;
    std::vector<int> data = numbers.getData();
    std::vector<int> choose;
    std::vector<bool> vis(n + 1);
    std::function<void(int)> dfs = [&](int now) {
        if (choose.size() > 7) return;
        if (now == n) {
            if (choose.size() != 7) return;
            ret += getPrize7((CustomSet<int>(choose.data(), 7) & prizeNumbers).size());
            return;
        }
        vis[now] = true;
        choose.push_back(data[now]);
        dfs(now + 1);
        choose.pop_back();
        vis[now] = false;
        dfs(now + 1);
    };
    dfs(0);
    hasClaimed = true;
    return ret;
}