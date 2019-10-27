/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @author Hongtu Xu
 * @date 2019-9-25
 */
#ifndef XUHONGTU
#undef _DEBUG
#define NDEBUG
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

typedef int VectorType;

typedef struct {
    VectorType *a;
    int n, cap;
} Vector;

#ifdef _DEBUG
void checkNullPointer(void *p, const char *s) {
    if (!p) {
        fputs(s, stderr);
        exit(0);
    }
}
#endif

Vector *newVector() {
    Vector *p = malloc(sizeof(Vector));
#ifdef _DEBUG
    checkNullPointer(p, "malloc vector failed");
#endif
    p->a = malloc((p->cap = 5) * sizeof(VectorType));
#ifdef _DEBUG
    checkNullPointer(p->a, "malloc array failed");
#endif
    p->n = 0;
    return p;
}

void pushBack(Vector *p, VectorType x) {
#ifdef _DEBUG
    checkNullPointer(p, "null pointer in func pushBack");
#endif
    p->a[p->n++] = x;
    if (p->n >= p->cap) {
        printf("(resize) from %d to %d\n", p->cap, p->cap * 2);
        p->cap *= 2;
        p->a = realloc(p->a, p->cap * sizeof(VectorType));
#ifdef _DEBUG
        checkNullPointer(p->a, "realloc failed");
#endif
    }
}

void release(Vector **d) {
#ifdef _DEBUG
    checkNullPointer(*d, "null pointer in func release");
#endif
    free((*d)->a);
    (*d)->n = (*d)->cap = 0;
    free(*d);
    *d = NULL;
}

long long mabs(long long x) { return x > 0 ? x : -x; }

void solve();

int main() {
#if !defined(ONLINE_JUDGE) && defined(_DEBUG) && defined(XUHONGTU)
    freopen("1.in", "r", stdin);
    clock_t dStart = clock(), dEnd;
#endif
    solve();
#if !defined(ONLINE_JUDGE) && defined(_DEBUG) && defined(XUHONGTU)
    dEnd = clock();
    fprintf(stderr, "\n%dms\n", (int)(dEnd - dStart));
#endif
}

void solve() {
    Vector *a = newVector(), *b = newVector();
    puts("Please input the set A:");
    for (int x;;) {
        scanf("%d", &x);
        if (x == -1) break;
        pushBack(a, x);
    }
    puts("Please input the set B:");
    for (int x;;) {
        scanf("%d", &x);
        if (x == -1) break;
        pushBack(b, x);
    }
    const int n = a->n;
    const int m = b->n;
    int *pAns = a->a;
    long long ans = LLONG_MAX;
    for (int i = 0; i + m <= n; i++) {
        long long sum = 0;
        for (int j = 0; j < m; j++) {
            sum += mabs((long long)a->a[i + j] - b->a[j]);
        }
        if (sum < ans) {
            pAns = a->a + i;
            ans = sum;
        }
    }
    puts("---Result---");
    for (int i = 0; i < m; i++) printf("%d ", pAns[i]);
    release(&a);
    release(&b);
}