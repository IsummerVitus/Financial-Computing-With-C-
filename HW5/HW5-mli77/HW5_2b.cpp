//
//  main.cpp
//  HW5_2b
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

void nr(double *x,int size,double *x1,int N)
{
    double S=28.0;double K[]={17.5,20,22.5,25,27.5,30,32.5};double p[]={0.28,0.48,0.81,1.41,2.42,3.8,5.56};double r=0;double tau=1;//const double pi=3.14159265358979323846264338328;
    double *temp=new double[size];
    for(int j=0;j<size;j++)
    {
        temp[j]=0;
    }

    

    for (int j=0;j<size;j++)
    {
        double c1,c2;
        //double *d=new double[size];
        for(int i=1;i<N;i++)
        {
            c1=BlackScholesPut(S, K[j], x1[j], tau, r)-p[j];
            c2=BlackScholesPut(S, K[j], x[j], tau, r)-p[j];
            temp[j]=x1[j]-c1*(x1[j]-x[j])/(c1-c2);
            if (fabs(temp[j] - x1[j]) < 0.0000001)
                break;
            x[j]=x1[j];
            x1[j]=temp[j];
            //cout<<" "<<x[j]<<" "<<x1[j]<<" "<<c1-c2;
            //d[j]=(log(S/K[j])+(r+x1[j]*x1[j]/2)*tau)/(x1[j]*sqrt(tau));
            //temp[j]=x1[j];
            //x1[j]=x1[j]-(BlackScholesPut(S, K[j], x1[j], tau, r)-p[j])*(x1[j]-x[j])
            ///((BlackScholesPut(S, K[j], x1[j], tau, r)-p[j])-(BlackScholesPut(S, K[j], x[j], tau, r)-p[j]));
            //x[j]=temp[j];
            
        }
        //cout<<endl;
        //cout<<endl;
    }
}
int main()
{
    double x[7]={0.01,0.01,0.01,0.01,0.01,0.01,0.01,};double x1[7]={0.5,0.9,0.9,0.9,0.9,0.9,0.9};
    nr(x,7,x1,100);
    for(int i=0;i<7;i++)
    {
        cout<<" "<<x1[i];
    }
}

