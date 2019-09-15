#pragma once

#define S_POINT2(T)                              \
    typedef struct point2_##T                    \
    {                                            \
        T x;                                     \
        T y;                                     \
    } s_point2_##T

#define S_POINT3(T)                              \
    typedef struct point3_##T                    \
    {                                            \
        T x;                                     \
        T y;                                     \
        T z;                                     \
    } s_point3_##T

S_POINT2(int);
S_POINT3(int);

S_POINT2(unsigned);
S_POINT3(unsigned);

S_POINT2(float);
S_POINT3(float);

S_POINT2(double);
S_POINT3(double);
