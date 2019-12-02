/**
 * Copyright (c) 2019, HongtuXu
 * All rights reserved.
 *
 * @author HongtuXu
 * @date 2019-11-17
 */
#ifndef _LOTTERYSTATION_H_
#define _LOTTERYSTATION_H_
#include "tickets.h"
#include <cstdlib>
#include <vector>

class LotteryStation {
   public:
    LotteryStation();
    ~LotteryStation();

    LotteryTicket *buy(CustomSet<int> numbers, int tickettype);
    // Represents buying a ticket of "tickettype" with "numbers" at round "m_round".
    // "tickettype" is either LOTTO6 or LOTTO7 (predefined).
    // If succeeds, output a message:
    // "Bought a (??) ticket for (??) Yuan at round (??).\n", then return a pointer to it.
    // See examples for more details.
    // If the numbers are not enough, or some numbers are out of bound for the ticket,
    //   output "Failed.\n" and return nullptr(NULL).

    void claimPrize(LotteryTicket *ticket);
    // Claims prize for a given ticket.
    // You should use the claimPrize() function of the ticket.
    // However, you should check the type of the ticket first,
    //   as you need to pass the right prize numbers as parameter.
    // Output a message in the end:
    // "This ticket wins (??) Yuan.\n"
    // You should not claim a ticket that's already claimed or with wrong rounds.
    // In either case above, simply print: "This ticket wins 0 Yuan.\n"

    void newRound();
    // Begins a new round, generating new prize numbers for Lotto7 and Lotto6.
    // You may use the randInt() function given.

    const bool setPrizeNumbers(CustomSet<int> numbers, int tickettype);
    // This function simply serves for the purpose of:
    // Making it easier for you to debug, and also easier for us to check your results.
    // It sets the prize numbers of the type given as the "numbers".
    // "tickettype" is either LOTTO6 or LOTTO7 (predefined).
    // If "numbers" are invalid (not enough/out of bounds), do nothing and return false.
    // If succeeded, return true.

   private:
    int m_round;  // Should be initialized to 0.
                  // Other private variables...
    CustomSet<int> prize6, prize7;
};
#endif