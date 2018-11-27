//
//  main.cpp
//  hw5
//
//  Created by Li M on 15/10/5.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include<cstdlib>
#include<ctime>
#include<stdio.h>
#include<math.h>
#include<iostream>

using namespace std;
int main()
{
    srand( static_cast<unsigned int>(time(NULL)));
    const double T=1,S0=100,r=0.05,sigma=0.2,K=100;
    const int N=10000;
    //const double pi=3.14159265358979323846264338328;
    double u1,u2,u3;
    double y;
    double z[N];
    
    for (int i=0;i<N;)
    {
        u1=rand()/(static_cast<double>(RAND_MAX)+1);
         u2=rand()/(static_cast<double>(RAND_MAX)+1);
         u3=rand()/(static_cast<double>(RAND_MAX)+1);
        y=-log(u1);
        if(u2<=exp(-pow(y-1,2)/2))
        {
            if(u3<0.5)
                z[i]=fabs(y);
            else
                z[i]=-fabs(y);
            i++;
            
        }
        
    }
    
    
    
    double S[N];
    double C[N];
    double sum=0;//double p=0;
    for(int i=0;i<N;i++)
    {
        S[i]=S0*exp((r-pow(sigma,2)/2)*T+sigma*pow(T,1/2)*z[i]);
        if(S[i]>K)
        {C[i]=exp(-r*T)*(S[i]-K);
            // p++;
        }
        else
            C[i]=0;
        sum+=C[i];
        //cout<<" "<<C[i];
    }
    sum=sum/N;
    cout<<"the price of option from accept-reject method is:"<<sum<<endl;
    
    //Marsaglia method below
    double u4,u5;
    double Z[N];
    for(int i=0;i<N;)
    {
        u4=rand()/(static_cast<double>(RAND_MAX)+1)*2-1;
        u5=rand()/(static_cast<double>(RAND_MAX)+1)*2-1;
        double s=pow(u4,2)+pow(u5,2);
        if(s<1)
        {
            Z[i]=u4*sqrt(-2*log(s)/s);
            i++;
        }
    }
    double S2[N];
    double C2[N];
    double sum2=0;
    for(int i=0;i<N;i++)
    {
        S2[i]=S0*exp((r-pow(sigma,2)/2)*T+sigma*sqrt(T)*Z[i]);
        
        if(S2[i]>K)
        {
            C2[i]=exp(-r*T)*(S2[i]-K);
            
            
        }
        
        else
            C2[i]=0;
        sum2+=C2[i];
        //cout<<" "<<C2[i];
        
    }
    sum2=sum2/N;//cout<<"m="<<m;cout<<"p="<<p;
    cout<<"the price of option from Marsaglia method is:"<<sum2<<endl;
    


}