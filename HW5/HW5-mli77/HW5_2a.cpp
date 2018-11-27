//
//  main.cpp
//  HW5_2
//
//  Created by Li M on 15/10/4.
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

void nr(double *x,int size,int N)
{
    double S=28.0;double K[]={17.5,20,22.5,25,27.5,30,32.5};double p[]={0.28,0.48,0.81,1.41,2.42,3.8,5.56};double r=0;double tau=1;const double pi=3.14159265358979323846264338328;
    
    for (int i=1;i<N;i++)
    {
        double d[size];
        for(int j=0;j<size;j++)
        {
            
            d[j]=(log(S/K[j])+(r+x[j]*x[j]/2)*tau)/(x[j]*sqrt(tau));
            x[j]=x[j]-(BlackScholesPut(S, K[j], x[j], tau, r)-p[j])/(S*1/sqrt(2*pi)*exp(-d[j]*d[j]/2)*pow(tau,1/2));
            
        }
        
    }
}
int main()
{
    double x[7]={0.3,0.3,0.3,0.3,0.3,0.3,0.3};
    nr(x,7,10000);
    for(int i=0;i<7;i++)
    {
        cout<<" "<<x[i];
    }
}






















