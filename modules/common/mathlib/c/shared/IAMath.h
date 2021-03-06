#ifndef IAMath_h
#define IAMath_h

#include <math.h>
#include <stdbool.h>

#define PRECALCULATED_PI_DIVIDED_BY_180     0.017453
#define PRECALCULATED_180_DIVIDED_BY_PI    57.295780

#define degreesToRadians(degrees) (degrees * PRECALCULATED_PI_DIVIDED_BY_180)
#define radiansToDegrees(radians) (radians * PRECALCULATED_180_DIVIDED_BY_PI)

long IAMath_min(long value1, long value2);
long IAMath_max(long value1, long value2);

long IAMath_abs(long value);

bool IAMath_isPow2(long value);
double IAMath_log(double base, double result);
bool IAMath_isInt(double d);

long IAMath_roundUp(float value);

#endif
