/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @author Hongtu Xu
 * @date 7/22/2019
 */
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

float cal(float a, char op, float b) {
    switch (op) {
        case '-':
            return a - b;
        case '+':
            return a + b;
        case '*':
            return a * b;
        case '/':
            return a / b;
#ifdef _DEBUG
        default:
            fprintf(stderr, "invalid op %c\n", op);
            assert(0);
#endif
    }
    return 0;
}

#ifdef _DEBUG
void check(char op) { assert(op == 'y' || op == 'n'); }
#endif

void readCmd(char *op, int *flag) {
    do {
        *op = getchar();
    } while (!isalpha(*op));
#ifdef _DEBUG
    check(*op);
#endif
    *flag = *op == 'y';
}

int main() {
#if defined(XUHONGTU) && defined(_DEBUG)
    freopen("1.in", "r", stdin);
#endif
    int flag = 1;
    do {
        puts("Enter the arithmetic expression to be evaluated (e.g. 5 + 6):");
        float a, b;
        char op;
        scanf("%f %c %f", &a, &op, &b);
        printf("%.6f\n%s ", cal(a, op, b),
               "Did you want to enter another expression? (Enter 'y' or 'n'):");
        readCmd(&op, &flag);
    } while (flag);
    return 0;
}