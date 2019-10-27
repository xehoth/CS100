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

typedef float VectorType;

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
    puts("Please type scores to be calculated:");
    Vector *p = newVector();
    for (float x;;) {
        scanf("%f", &x);
        if (x == -1) break;
        pushBack(p, x);
    }
    const int n = p->n;
    VectorType tot = 0;
    for (int i = 0; i < n; i++) tot += p->a[i];
    printf("Average score: %.2f", tot / n);
    release(&p);
}