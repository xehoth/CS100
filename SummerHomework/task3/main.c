/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @author Hongtu Xu
 * @date 7/22/2019
 */
#include <stdio.h>
#include <math.h>

int main() {
#if defined(XUHONGTU) && defined(_DEBUG)
    freopen("1.in", "r", stdin);
#endif
    printf("What time is it? ");
    int hour, min;
    scanf("%d:%d", &hour, &min);
    hour %= 12;
    double aHour = (hour + min / 60.0) / 12.0 * 360;
    double aMin = min / 60.0 * 360;
    double ret = fabs(aHour - aMin);
    ret = fmin(ret, 360 - ret);
    printf("The angle between the hands is %.1f degrees.\n", ret); 
    return 0;
}