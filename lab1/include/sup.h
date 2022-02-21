#ifndef SUP_H
#define SUP_H

#include "../shapes/shapes"

void solve_nonlinear_system(sPoint p01, int r1, sPoint p02, int r2, 
sPoint *res1_p1, sPoint *res1_p2, 
sPoint *res2_p1, sPoint *res2_p2, 
sPoint *res3_p1, sPoint *res3_p2, 
sPoint *res4_p1, sPoint *res4_p2
);

int rightRound(double num);

#endif // SUP_H
