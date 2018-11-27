//
//  main.cpp
//  HW3_4
//
//  Created by Li M on 15/9/22.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include<iostream>
#include<math.h>


double ph(double x)
{
    double b[]={0.2316419,0.3193815300,-0.356563782,1.7814779370,-1.821255978,1.3302744290};
    double t=1/(1+b[0]);
    const double pi=3.14159265358979323846264338328;
    double pdf=1/sqrt(2*pi)*exp(-x*x/2);
    double s=0;
    for(int i=0;i<6;i++)
    {
        s+=pdf*b[i]*pow(t,(i+1));
    }
    s=1-s;
    return s;
}
double BlackScholesCall(double S,double K,double sigma,double tau,double r)
{
    double d1=(log(S/K)+(r+sigma*sigma/2)*tau)/(sigma*sqrt(tau));
    double d2=(log(S/K)+(r-sigma*sigma/2)*tau)/(sigma*sqrt(tau));
    return S*ph(d1)-K*exp(-r*tau)*ph(d2);
    
}
double BlackScholesPut(double S,double K,double sigma,double tau,double r)
{
    double d1=(log(S/K)+(r+sigma*sigma/2)*tau)/(sigma*sqrt(tau));
    double d2=(log(S/K)+(r-sigma*sigma/2)*tau)/(sigma*sqrt(tau));
    return -S*ph(-d1)+K*exp(-r*tau)*ph(-d2);
}