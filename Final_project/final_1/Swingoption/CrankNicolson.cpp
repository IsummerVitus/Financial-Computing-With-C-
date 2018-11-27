//
//  CrankNicolson.cpp
//  
//
//  Created by Li M on 15/12/18.
//
//

#include "CrankNicolson.h"
CrankNicolson:: CrankNicolson(vector<double>vl,vector<double> sl,double price_, double K_, double T_,double vol_, double rate_, int M_, int N_):price(price_),K(K_),T(T_),vol(vol_),rate(rate_),M(M_),N(N_)

{
    b.resize(2*M+1);
    c1.resize(2*M+1);
    d.resize(2*M+1);
    x.resize(2*M+1);
    dx = 0.0;              // state step size
    drift = rate - vol*vol/2;  // drift rate
    deltat = T/N;             // time step size
    dx = vol*sqrt(3*deltat/2);
    // we multiply by 0.5 because we are using Crank-Nicolson
    a = 0.5*(deltat/(dx*dx));
    // compute probabilities
    pu = -0.5*deltat*((vol*vol)/(dx*dx) + drift/dx);
    pm = 1 + deltat*(vol*vol/(dx*dx)) + rate*deltat;
    pd = -0.5*deltat*((vol*vol)/(dx*dx) - drift/dx);
    // calculate coefficients
    // calculate payoffs
    P.resize(N+1);
    for (int i = 0; i < N+1; i++) {
        P[i].resize(2*M+1,0);
    }
    for (j = -M; j <= M; j++)
    {
        P[N][j+M] = vl[j+M];
    }
    
    for (j = -M+1; j < M; j++)
        b[j+M] = (1-a)*P[N][j+M] + a*(P[N][j+1+M] + P[N][j-1+M]);
    b[-M+1+M]= b[-M+1+M] + a*P[N][-M+M];
    b[M-1+M] = b[M-1+M] + a*P[N][M+M];
    for (j = -M; j <= M; j++)
        d[j+M] = P[N][j+M];
    // set values at boundary points d1[-M] = d[-M]/pm;
    b[-M+1+M] = d[-M+1+M]/pm;
    c1[-M+M] = pd/pm;
    c1[-M+1+M] = pd/pm;
    
    for (j = -M+1; j <= M-2; j++)
        c1[j+1+M] = pd/(pm - pu*c1[j+M]);
    for (j = -M+1; j <= M-1; j++)
        b[j+1+M] = (d[j+1+M] - pu*b[j-1+M])/(pm - pu*c1[j+M]);
    // solve tridiagonal system
    for (i = N-1; i >= 0; i--)
    {
        for (j = -M+1; j <= M-1; j++)
        {
            if (i != N-1)
                d[j+M] = P[i+1][j+M];
            if (j == -M+1)
                b[-M+1+M] = d[-M+1+M]/pm;
            b[j+1+M] = (d[j+1+M] - pu*b[j-1+M])/(pm - pu*c1[j+M]);
            P[i][-j+M] = b[-j+M] - c1[-j+M]*P[i][-j+1+M];
            // check early exercise
            if (P[i][-j+M] < sl[-j+M] - K)
                P[i][-j+M] = sl[-j+M] - K;
        }
    }
    
}
double CrankNicolson::Max(double a,double b)
{
    if (a>=b)
        return a;
    else
        return b;
}
double CrankNicolson:: p()
{
    return P[0][M];
}

