//
//  main.cpp
//  HW5_1
//
//  Created by Li M on 15/10/4.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include<cstdlib>
#include<ctime>
#include<stdio.h>
#include<cmath>
#include<iostream>

using namespace std;
int main()
{
    srand( static_cast<unsigned int>(time(NULL)));
    const double T=1,S0=100,r=0.05,sigma=0.2,K=100;
    const int N=90000;
    const double pi=3.14159265358979323846264338328;
    double ia[N];
    for(int i=0;i<N;i++)
    {
        ia[i]=rand()/(static_cast<double>(RAND_MAX));
    }
    double ib[N];
    for(int i=0;i<N;i++)
    {
        ib[i]=rand()/(static_cast<double>(RAND_MAX));
    }
    double iz[2*N];
    for(int i=0;i<N;i++)
    {
        iz[2*i]=sqrt(-2*log(ia[i]))*cos(2*pi*ib[i]);
        iz[2*i+1]=sqrt(-2*log(ib[i]))*sin(2*pi*ia[i]);
    }
    double S[2*N];
    double C[2*N];
    double sum=0;
    for(int i=0;i<2*N;i++)
    {
        S[i]=S0*exp((r-pow(sigma,2)/2)*T+sigma*pow(T,1/2)*iz[i]);
        if(S[i]>K)
            C[i]=exp(-r*T)*(S[i]-K);
        else
            C[i]=0;
        sum+=C[i];
        
    }
    sum/=2*N;
    cout<<"the price of option from BOX-Muller method is:"<<sum<<endl;
    
}
