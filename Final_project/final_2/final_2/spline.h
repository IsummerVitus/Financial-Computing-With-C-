#ifndef INTERP_H_INCLUDED
#define INTERP_H_INCLUDED

#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;
double spline(int len, double* t, double* spotR, double x)    // parameters of spline polynomial
{
    double b[len-1], d[len-1], h[len-1], alpha[len-1];double *a = spotR;
    for (int i = 0; i < len-1; i++)
        h[i] = t[i+1] - t[i];
    alpha[0] = 0;
    for (int i = 1; i < len-1; i++)
        alpha[i] = 3/h[i] * (a[i+1]-a[i]) - 3/h[i-1] * (a[i]-a[i-1]);
    double c[len], l[len], u[len], z[len];
    l[0] = 1;u[0] = 0;z[0] = 0;
    for (int i = 1; i < len - 1; i++)
    {
        l[i] = 2*(t[i+1]-t[i-1]) - h[i-1]*u[i-1];
        u[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i-1]*z[i-1]) / l[i];
    }

    l[len-1] = 1;
    z[len-1] = 0;
    c[len-1] = 0;
    for (int j = len-2; j >= 0; j--)
    {
        c[j] = z[j] - u[j]*c[j+1];
        b[j] = (a[j+1]-a[j]) / h[j] - h[j]*(c[j+1]+2*c[j]) / 3;
        d[j] = (c[j+1] - c[j]) / 3 / h[j];
    }

    int p = 0;
    while (x > t[p] && p < len-1) p++;
    if (p > 0)
    {
        p--;
    }
    double pred = a[p] + b[p]*(x-t[p]) + c[p]*pow((x-t[p]),2) + d[p]*pow((x-t[p]),3);
    return pred;
}


#endif // INTERP_H_INCLUDED
