//
//  main.cpp
//  Swingoption
//
//  Created by Li M on 15/12/18.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#include "BuildScheme.h"
#include "CrankNicolson.h"

double Max(double a,double b)
{
    if (a>=b)
        return a;
    else
        return b;
}


int main()
{
    int N=9;int M=9;
    int K=50;int price=50;double T=1.0;double T1=1.0/3.0; double T2=2.0/3.0;
    double rate=0.07;double vol=0.2;
    vector<double> S2; //store possible stock price at time T2
    vector<double> S1;
    vector<double> S3;
    vector<double> V2; //store option price in situation k2(-)=2
    vector<double> V1;
    vector<double> V3;
    vector<double> v2; //store price in situation k2(-)=1
    double v;
    
    BuildScheme CN(price, K, T,vol, rate, M,N );
    S2.resize(2*T2*N+1);
    S1.resize(2*T1*N+1);
    S3.resize(2*T*N+1);
    V2.resize(2*T2*N+1);
    V1.resize(2*T1*N+1);
    V3.resize(2*T*N+1);
    v2.resize(2*T2*N+1);
    for (int i=0;i<2*M+1;i++)
    {
        S3[i]=CN.S[N][i];
        V3[i]=CN.P[N][i];
    }

    for(int i=0;i<2*T2*N+1;i++)
    {
        S2[i]=CN.S[T2*N][M-T2*N-1+i];
        CrankNicolson m(V3,S3,S2[i],K,T,vol,rate,M,N);
        V2[i]=Max(m.p(), S2[i]-K);
        //k2(-)=1, then we choose to exercise at T3 or T2, use S2[i] as initial price to conduct CrankNicolson method in interval [T2,T3)
        v2[i]=Max(S2[i]-K,0);     //k2(-)=2, then we exercise whenever it is optimal
        
        
    }

    for(int i=0;i<2*T1*N+1;i++)
    {
        S1[i]=CN.P[T1*N][M-T1*N-1+i];
        CrankNicolson m1(V2,S2,S1[i],K,T,vol,rate,T2*N,N);   // outcome of exercising at T1
        CrankNicolson m2(v2,S2,S1[i],K,T,vol,rate,T2*N,N);   // outcome of not exercsing at T1,say at T2
        V1[i]=Max(m1.p()+S1[i]-K, m2.p());          // compare above two choices
        
    }
    CrankNicolson m3(V1,S1,price,K,T,vol,rate,T1*N,N);
    v=m3.p();
    cout<<"the option price is:"<<v;
        
}
