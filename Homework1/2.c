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

typedef struct {
    float x, y;
} Point;

float sqr(float x) { return x * x; }

float dis(Point a, Point b) { return sqrtf(sqr(a.x - b.x) + sqr(a.y - b.y)); }

Point getCenter(Point *a, int n) {
    float x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        x += a[i].x;
        y += a[i].y;
    }
    return (Point){x / n, y / n};
}

int main() {
#if !defined(ONLINE_JUDGE) && defined(_DEBUG) && defined(XUHONGTU)
    freopen("1.in", "r", stdin);
    clock_t dStart = clock(), dEnd;
#endif
    Point a[3];
    for (int i = 0; i < 3; i++) {
        printf("Input vertex %d: ", i + 1);
        scanf("%f %f", &a[i].x, &a[i].y);
    }
    Point c = getCenter(a, 3);
    printf("The center of the triangle is: %.1f %.1f\n", c.x, c.y);
    float dMax = max(dis(c, a[0]), max(dis(c, a[1]), dis(c, a[2])));
    float dMin = min(dis(c, a[0]), min(dis(c, a[1]), dis(c, a[2])));
    printf("The maximum distance between center and vertices: %.2f\n", dMax);
    printf("The minimum distance between center and vertices: %.2f", dMin);
#if !defined(ONLINE_JUDGE) && defined(_DEBUG) && defined(XUHONGTU)
    dEnd = clock();
    fprintf(stderr, "%dms\n", (dEnd - dStart));
#endif
    return 0;
}