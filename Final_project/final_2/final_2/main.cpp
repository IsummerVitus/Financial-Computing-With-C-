#include <iostream>
#include <vector>
#include "spline.h"
#include "HWTree.h"
#include <cmath>
#include <math.h>

using namespace std;

int main()
{
    double term[10] = {0.0795, 0.2521, 0.5014, 0.9425, 1.9836, 3.0247, 4.9863, 6.9863, 9.8630, 29.877};
    // Time to maturity
    double price[10] = {100, 100, 99.96, 99.77, 100.002, 99.85, 100.076, 100.054, 99.738, 100.194};
    double spotR[10] = {};   //spotrate
    spotR[2] = -log(price[2]/100) / term[2];
    spotR[3] = -log(price[3]/100) / term[3];
    vector <double> zeroR;
    vector <double> payoff;
    vector <double> zerocoupon;     // zero coupon rate in the whole period
    double vol = 0.2;           //volatility
    double dt = 0.25;
    double deltat = 0.01;      //delta t in interval[5,5.25)
    double BP;                 // B(t,t+delta) generated from HWTree.cpp
    double L;                  // LIBOR rate
    double a = 1.0;
    double T = 5.0;
    int step = dt/deltat+1;
    int N=1000000;
    double K = 0.01;
    for (int x = 0; x < step; x++)
        zeroR.push_back(spline(10, term, spotR, T+deltat*(x+1)));   //use spline get zero rate in interval
    HWTree buildHW(zeroR, a, vol, step, dt);
    BP = buildHW.bp();
    L = (1-BP)/dt/BP;
    payoff.push_back(max(L-K,0.0));
    zerocoupon.push_back(spline(10, term, spotR, T+dt));
    for (int x = 0; x < step; x++)
    {
        zeroR.pop_back();
    }

    double payment = payoff[T/dt] * exp(-zerocoupon[T/dt]*(T/dt+1)*dt)*N*dt;
    //caplet in the interval[5, 5.25)
    cout << "The price of caplet is:"<<payment << endl;

}



