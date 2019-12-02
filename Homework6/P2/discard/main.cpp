#include "lotterystation.h"

int main() {
    int a[] = {2, 7, 16, 21, 22, 23};
    int t[] = {2, 7, 16, 21, 24, 23, 37, 43};
    CustomSet<int> foo(a, 6);
    CustomSet<int> ticket(t, 8);
    LotteryStation sample;
    sample.newRound();
    sample.setPrizeNumbers(foo, LOTTO6);  // LOTTO6 is predefined
    LotteryTicket *jackpot = sample.buy(ticket, LOTTO6);
    // // prints "Bought a Lotto 6 ticket for 2 Yuan at round 1.\n"
    sample.claimPrize(jackpot);
    // prints "This ticket wins 2000000 Yuan.\n"
    delete jackpot;
}