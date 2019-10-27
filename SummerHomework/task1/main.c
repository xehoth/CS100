/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @author Hongtu Xu
 * @date 7/22/2019
 */
#include <stdio.h>

#define MAXN 90

unsigned long long fib[MAXN] = {0, 1};

int main() {
#if defined(XUHONGTU) && defined(_DEBUG)
    freopen("1.out", "w", stdout);
#endif

    for (int i = 2; i < MAXN; i++) fib[i] = fib[i - 1] + fib[i - 2];
    for (int i = 0; i < MAXN; i++) printf("The next number is %llu\n", fib[i]);
    return 0;
}