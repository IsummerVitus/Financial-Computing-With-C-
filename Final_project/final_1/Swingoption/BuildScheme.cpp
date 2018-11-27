//
//  BuildScheme.cpp
//  Swingoption
//
//  Created by Li M on 15/12/18.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#include "BuildScheme.h"
BuildScheme::BuildScheme(double price_, double K_, double T_,double vol_, double rate_, int M_, int N_):price(price_),K(K_),T(T_),vol(vol_),rate(rate_),M(M_),N(N_)

{
    b.resize(2*M+1);
    c1.resize(2*M+1);
    d.resize(2*M+1);
    x.resize(2*M+1);
    dx = 0.0;              // state step size
    drift = rate - vol*vol/2;  // drift rate
    deltat = T/N;             // time step size
    //cout.setf(ios::showpoint);
    //cout.precision(2);
    dx = vol*sqrt(3*deltat/2);
    // we multiply by 0.5 because we are using Crank-Nicolson
    a = 0.5*(deltat/(dx*dx));
    // compute probabilities
    pu = -0.5*deltat*((vol*vol)/(dx*dx) + drift/dx);
    pm = 1 + deltat*(vol*vol/(dx*dx)) + rate*deltat;
    pd = -0.5*deltat*((vol*vol)/(dx*dx) - drift/dx);
    // calculate coefficients
    S.resize(N+1);
    for (int i = 0; i < N+1; i++) {
        S[i].resize(2*M+1,0);
    }                                 // a scheme  of (N+1)* 2M+1
    for (j = -M; j <= M; j++)
    {
        S[N][j+M] = price*exp(j*dx);
        S[0][j+M] = price;
    }
    // compute stock prices
    for (i = 1; i < N; i++)
    {
        for (j = -M; j <= M; j++)
            S[i][j+M] = S[i-1][j+M]*exp(j*dx);
    }
    // calculate payoffs
    P.resize(N+1);
    for (int i = 0; i < N+1; i++) {
        P[i].resize(2*M,0);
    }
    for (j = -M; j <= M; j++)
    {
        P[N][j+M] = Max(S[N][j+M] - K,0);
    }
    // calculate boundary conditions
    for (i = 0; i < N; i++)
    {
        P[i][M+M] = P[i][M-1+M] + (S[i][M+M] - S[i][M-1+M]); // derivative boundary condition
        P[i][-M+M] = 0;
    }
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
            if (P[i][-j+M] < S[N][-j+M] - K)
                P[i][-j+M] = S[N][-j+M] - K;
        }
    }
    
    
    
}
double BuildScheme:: Max(double a,double b)
{
    if (a>=b)
        return a;
    else
        return b;
}

