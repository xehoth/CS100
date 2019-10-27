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

float max(float a, float b) { return a > b ? a : b; }
float min(float a, float b) { return a < b ? a : b; }

int main() {
#if !defined(ONLINE_JUDGE) && defined(_DEBUG) && defined(XUHONGTU)
    freopen("1.in", "r", stdin);
    clock_t dStart = clock(), dEnd;
#endif
    printf("Please type number of inputs: ");
    int n;
    scanf("%d", &n);
    float aMax = FLT_MIN, aMin = FLT_MAX, x;
    for (int i = 0; i < n; i++) {
        scanf("%f", &x);
        aMax = max(aMax, x);
        aMin = min(aMin, x);
    }
    printf("Max value: %.1f\nMin value: %.1f", aMax, aMin);
#if !defined(ONLINE_JUDGE) && defined(_DEBUG) && defined(XUHONGTU)
    dEnd = clock();
    fprintf(stderr, "%dms\n", (dEnd - dStart));
#endif
    return 0;
}
