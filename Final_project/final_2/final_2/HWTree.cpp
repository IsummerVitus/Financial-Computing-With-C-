//
//  HWTree.cpp
//  IRofHWTree
//
//  Created by Li M on 15/12/17.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#include "HWTree.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

HWTree::HWTree(vector<double> zeroRate,
               double Speed_,
               double Volatility_,
               long Steps_,
               double Time_)
: Speed(Speed_),
Volatility(Volatility_),
Steps(Steps_),
Time(Time_)
{
    TheTree.resize(Steps + 1);
    r.resize(Steps + 1);
    Q.resize(Steps + 1);
    BP.resize(Steps+1);
    for (long i = 0; i <= Steps; i++)
    {
        TheTree[i].resize(2*i+1);
        r[i].resize(2 * i + 1);
        Q[i].resize(2 * i + 1);
        BP[i].resize(2*i+1);
    }
    long i, j, k;
    long jmax;
    long jmin;
    vector<double> pu(2*Steps+1);
    vector<double> pm(2*Steps+1);
    vector<double> pd(2*Steps+1);
    double sum = 0.0;
    double sum1 = 0.0;
    vector<double> sum2(2*Steps+1);
    vector<double> alpha(Steps+1);
    vector<double> B(Steps+2);
    double dt = Time / Steps;
    double dr = Volatility*sqrt(3 * dt);
    double a = Speed;
    jmax = (int long)ceil(0.184 / (a*dt));
    jmin = -jmax;
    B[0] = 1;
    
    for (i = 0; i <= Steps; ++i)
    {
        for (j = i; j >= -i; --j)
        {
            if ( j == jmax) {
                pu[j+i] = 1.167 + 0.5*(a*a*j*j*dt*dt - 3 * a*j*dt);
                pm[j+i] = -0.333 - a*a*j*j*dt*dt + 2 * a*j*dt;
                pd[j+i] = 0.167 + 0.5*(a*a*j*j*dt*dt - a*j*dt);
            } else if (j == jmin) {
                pu[j+i] = 0.167 + 0.5*(a*a*j*j*dt*dt + a*j*dt);
                pm[j+i] = -0.333 - a*a*j*j*dt*dt - 2 * a*j*dt;
                pd[j+i] = 1.167 + 0.5*(a*a*j*j*dt*dt + 3 * a*j*dt);
            } else {
                pu[j+i] = 0.167 + 0.5*(a*a*j*j*dt*dt - a*j*dt);
                pm[j+i] = 0.666 - a*a*j*j*dt*dt;
                pd[j+i] = 0.167 + 0.5*(a*a*j*j*dt*dt + a*j*dt);
            }
        }
    }
    
    for (i = 0; i <= Steps; ++i) {
        for (j = i; j >= -i; --j) {
            r[i][j+i] = j*dr;
        }
    }
    
    alpha[0] = zeroRate[0];
    r[0][0] = alpha[0];
    Q[0][0] = 1.0;
    
    for (i = 0; i <= Steps; ++i) {
        B[i + 1] = exp(-zeroRate[i] * (i + 1)*dt);
    }
    
    for (jmax = 0; jmax <= Steps-1; ++jmax)
    {
        sum = 0;
        sum1 = 0;
        for (j = jmax + 1; j >= -(jmax + 1); j--)
        {
            sum2[j+jmax+1] = 0;
        }
        for (j = jmax; j >= -jmax; j--)
        {
            sum1 += (Q[jmax][j+jmax] * exp(-j*dr*dt));
        }
        alpha[jmax] = (1 / dt)*(log(sum1 / B[jmax + 1]));
        
        for (j = jmax; j >= -jmax; j--)
        {
            sum += Q[jmax][j+jmax] * exp(-(alpha[jmax] + j*dr)*dt);
        }
        
        if (jmax == 0) {
            Q[1][1+1] = 0.167*exp(-(alpha[jmax] + dr));
            Q[1][0+1] = 0.666*exp(-alpha[jmax]);
            Q[1][-1+1] = 0.167*exp(-(alpha[jmax] - dr));
        } else {
            for (k = jmax; k >= -jmax; --k) {
                for (j = k + 1; j >= k - 1; --j) {
                    if (j == jmax + 1) {
                        Q[jmax + 1][jmax + 1+ jmax + 1] = Q[jmax][jmax+jmax] * pu[jmax+jmax] * (-(alpha[jmax] +
                                                                                                  jmax*dr)*dt);
                    }
                    if (j == -(jmax + 1)) {
                        Q[jmax + 1][0] = Q[jmax][0] * pd[-jmax+jmax] * (-(alpha[jmax] +
                                                                          (-jmax)*dr)*dt);
                    }
                    if ((pu[k+jmax] > 0) && (j - k == 1)) {
                        sum2[j+jmax+1] += Q[jmax][k+jmax] * pu[k+jmax] * exp(-(alpha[jmax] + k*dr)*dt);
                    }
                    if ((pm[k+jmax] > 0) && (j - k == 0)) {
                        sum2[j+jmax+1] += Q[jmax][k+jmax] * pm[k+jmax] * exp(-(alpha[jmax] + k*dr)*dt);
                    }
                    if ((pd[k+jmax] > 0) && (j - k == -1)) {
                        sum2[j+jmax+1] += Q[jmax][k+jmax] * pd[k+jmax] * exp(-(alpha[jmax] + k*dr)*dt);
                    }
                    Q[jmax + 1][j+jmax+1] = sum2[j+jmax+1];
                }
            }
        }
        if (jmax == Steps - 1) {
            sum1 = 0;
            for (j = jmax+1; j >= -jmax-1; --j) {
                sum1 += (Q[jmax + 1][j + jmax + 1] * exp(-j*dr*dt));
            }
            alpha[jmax+1] = (1 / dt)*(log(sum1 / B[jmax + 1 + 1]));
        }
    }
    
    r[0][0] = 0;
    for (i = 0; i <= Steps; ++i)
    {
        for (j = i; j >= -i; --j)
        {
            TheTree[i][j+i] = alpha[i] + r[i][j+i];
            BP[i][j] = 1;  
        }
    }
    
    for (i = Steps-1; i >= 0; i--)
    {
        for (j = i; j >= -i; j--)
        {
            BP[i][j] = pu[j+1]*BP[i+1][j+1]*exp(-TheTree[i+1][j+1]*dt)
            + pm[j]*BP[i+1][j]*exp(-TheTree[i+1][j]*dt)
            + pd[j-1]*BP[i+1][j-1]*exp(-TheTree[i+1][j-1]*dt);
        }
    }
    
}

double HWTree::bp()
{
    return BP[0][0];
   
}

void HWTree::printQ()
{
    for (long i = 0; i <= Steps; ++i) {
        for (long j = i; j >= -i; --j) {
            cout << Q[i][j + i] << " ";
        }
        cout << endl;
    }
}