/**
 * Copyright (c) 2019, HongtuXu
 * All rights reserved.
 *
 * @author HongtuXu
 * @date 2019-11-17
 */
#ifndef _TICKETS_H_
#define _TICKETS_H_
#ifndef LOTTO6
#define LOTTO6 6
#endif
#ifndef LOTTO7
#define LOTTO7 7
#endif
#include "customset.h"

inline int getBinom(int n, int r) {
    static const int MAX_COMBINATION = 50;
    static int c[MAX_COMBINATION][MAX_COMBINATION];
    static bool flag = false;
    if (!flag) {
        for (int i = 0; i < MAX_COMBINATION; ++i) c[i][0] = 1;
        for (int i = 1; i < MAX_COMBINATION; ++i)
            for (int j = 1; j <= i; ++j) c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        flag = true;
    }
    return c[n][r];
}

class LotteryTicket {
   public:
    LotteryTicket();
    LotteryTicket(const CustomSet<int> &numbers, int round);
    virtual ~LotteryTicket();

    const int getRound() const;
    const int getCost() const;
    virtual const int getTicketType() const = 0;
    void setCost(const int &cost);
    virtual const int claimPrize(const CustomSet<int> &prizeNumbers, int round) = 0;

    //
    const CustomSet<int> &getNumbers() const { return m_numbers; }
    CustomSet<int> &getNumbers() { return m_numbers; }

   protected:
    bool hasClaimed;

   private:
    CustomSet<int> m_numbers;
    int m_round;  // The valid round of a ticket. An outdated ticket is invalid.
    int m_cost;   // The amount of money spent on this ticket.
};

class Lotto6Ticket : public LotteryTicket {
   public:
    Lotto6Ticket(const CustomSet<int> &numbers, int round);
    virtual ~Lotto6Ticket();
    const int getTicketType() const override;
    const int claimPrize(const CustomSet<int> &prizeNumbers, int round) override;
};

class Lotto7Ticket : public LotteryTicket {
   public:
    Lotto7Ticket(const CustomSet<int> &numbers, int round);
    virtual ~Lotto7Ticket();
    const int getTicketType() const override;
    const int claimPrize(const CustomSet<int> &prizeNumbers, int round) override;
};
#endif