/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @author Hongtu Xu
 * @date 7/22/2019
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 5000
#define BUF_LEN ((10 * MAXN / 3) + 1)

int getNum(int i) { return i - 1; }

int getDen(int i) { return 2 * i - 1; }

void divide(int a, int b, int *q, int *r) {
    *q = a / b;
    *r = a % b;
}

void fillN(int *a, int n, int val) {
    for (int i = 0; i < n; i++) a[i] = val;
}

typedef struct {
    char *s;
    int cur, size;
} String;

void append(String *s, char c, int t) {
    while (t--) {
        if (s->cur >= s->size) {
            s->size *= 2;
            s->s = realloc(s->s, s->size);
        }
        s->s[s->cur++] = c;
    }
}

String *newString() {
    String *s = malloc(sizeof(String));
    s->s = malloc(s->size = 1);
    s->cur = 0;
    return s;
}

void release(String **s) {
    free((*s)->s);
    free(*s);
    *s = NULL;
}

void spigotAlgorithm(int n) {
    int len = 10 * n / 3 + 1, pre = 0;
    int *a = malloc(sizeof(int) * len);
    fillN(a, len, 2);
    String *s = newString();

    for (int q, carry, cnt9 = 0, *b = a - 1; n--;) {
        q = carry = 0;
        for (int i = len; i > 0; carry = q * getNum(i--))
            divide(b[i] * 10 + carry, getDen(i), &q, b + i);
        divide(q, 10, &q, a);
        cnt9 += q == 9;
        if (q == 10) {
            append(s, pre + 49, 1);
            append(s, 48, cnt9);
            cnt9 = pre = 0;
        }
        if (q < 9) {
            append(s, pre + 48, 1);
            pre = q;
            append(s, 57, cnt9);
            cnt9 = 0;
        }
    }
    append(s, pre + 48, 1);
    printf("3.%s", s->s + 2);
    free(a);
    release(&s);
}

int main() {
#if defined(XUHONGTU) && defined(_DEBUG)
    clock_t start, end;
    start = clock();
#endif
    spigotAlgorithm(5000);

#if defined(XUHONGTU) && defined(_DEBUG)
    end = clock();
    fprintf(stderr, "%ldms\n", (end - start));
#endif
    return 0;
}