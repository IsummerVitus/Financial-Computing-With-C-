//
//  BS.h
//  HW10
//
//  Created by Li M on 15/11/20.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#ifndef HW10_BS_h
#define HW10_BS_h
#include<iostream>
#include<math.h>
using namespace std;
double ph(double x)
{
    if (x>=0)
    {
        double b[]={0.2316419,0.3193815300,-0.356563782,1.7814779370,-1.821255978,1.3302744290};
        double t=1/(1+b[0]*x);
        const double pi=3.14159265358979323846264338328;
        double pdf=1/sqrt(2*pi)*exp(-x*x/2);
        double s=0;
        for(int i=1;i<6;i++)
        {
            s+=pdf*b[i]*pow(t,i);
        }
        s=1-s;
        return s;
    }
    else
    {
        x=-x;
        double b[]={0.2316419,0.3193815300,-0.356563782,1.7814779370,-1.821255978,1.3302744290};
        double t=1/(1+b[0]*x);
        const double pi=3.14159265358979323846264338328;
        double pdf=1/sqrt(2*pi)*exp(-x*x/2);
        double s=0;
        for(int i=1;i<6;i++)
        {
            s+=pdf*b[i]*pow(t,i);
        }
        return s;
        
    }
    
}

double BlackScholesCall(double S,double K,double sigma,double tau,double r)
{
    double d1=(log(S/K)+(r+sigma*sigma/2)*tau)/(sigma*sqrt(tau));
    double d2=(log(S/K)+(r-sigma*sigma/2)*tau)/(sigma*sqrt(tau));
    return S*ph(d1)-K*exp(-r*tau)*ph(d2);
}


#endif
