//
//  main.cpp
//  HW4_4
//
//  Created by Li M on 15/9/28.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
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
double BlackScholesPut(double S,double K,double sigma,double tau,double r)
{
    double d1=(log(S/K)+(r+sigma*sigma/2)*tau)/(sigma*sqrt(tau));
    double d2=(log(S/K)+(r-sigma*sigma/2)*tau)/(sigma*sqrt(tau));
    return -S*ph(-d1)+K*exp(-r*tau)*ph(-d2);
}
double f(double x)
{
    double S=28.0;double K=32.5;double p=5.56;double r=0;double tau=1;
    //cout<<"please input the strike price"<<endl;cin>>K;
    //cout<<"please input the price of option"<<endl;cin>>p;
    double m=BlackScholesPut(S, K, x, tau, r);
    return m-p;
}
double bs(double low,double high)
{
    double c;double e1=0.00001;double e2=0.00001;
    c=(low+high)/2;
    do
    {
        
        if (fabs(f(c))<=e1)
        {
            return c;
            break;
        }
        else
        {
            if (f(low)*f(c)<0)
                high=c;
            else
                low=c;
        }
        c=(low+high)/2;
        
    }
    while ((fabs(high-low))>e2);
    c=(low+high)/2;
    return c;
}



int main()
{
    double t=bs(0.01,0.9);
    cout<<t;
}







