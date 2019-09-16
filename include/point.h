#pragma once

#define S_POINTS(T)                              \
    typedef struct point2_##T                    \
    {                                            \
        T x;                                     \
        T y;                                     \
    } s_point2_##T;                              \
    typedef struct point3_##T                    \
    {                                            \
        T x;                                     \
        T y;                                     \
        T z;                                     \
    } s_point3_##T

S_POINTS(int);
S_POINTS(unsigned);
S_POINTS(float);
S_POINTS(double);

typedef s_point2_unsigned t_dimension;
