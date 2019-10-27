/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @author Hongtu Xu
 * @date 2019-9-18
 */
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <float.h>

#define MAXN 840

typedef struct {
    int l, r;
} Lecture;

Lecture a[MAXN + 10];

float min(float a, float b) { return a < b ? a : b; }
int vis[MAXN + 10];

int main() {
#if !defined(ONLINE_JUDGE) && defined(_DEBUG) && defined(XUHONGTU)
    freopen("1.in", "r", stdin);
    clock_t dStart = clock(), dEnd;
#endif
    puts("How many lectures today?");
    int n;
    scanf("%d", &n);
    for (int i = 0, h, m; i < n; i++) {
        scanf("%d:%d-", &h, &m);
        a[i].l = (h - 8) * 60 + m;
        scanf("%d:%d", &h, &m);
        a[i].r = (h - 8) * 60 + m;
    }
    float mood = 100;
    for (int i = 0; i < 840; i++) vis[i] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = a[i].l; j < a[i].r; j++) vis[j] = 0;
    }
    int cnt = 0;
    for (int i = 0; i < 840; i++) {
        if (vis[i]) {
            mood = min(100, mood + 0.5);
            cnt = 0;
        } else {
            cnt++;
            if (cnt <= 60)
                mood -= 0.4;
            else
                mood -= 0.8;
            if (mood <= 0) {
                printf("Gezi Wang has been sent to hospital.");
                return 0;
            }
        }
    }
    printf("His mood level is %.1f at the end of the day.", mood);
#if !defined(ONLINE_JUDGE) && defined(_DEBUG) && defined(XUHONGTU)
    dEnd = clock();
    fprintf(stderr, "%dms\n", (dEnd - dStart));
#endif
    return 0;
}