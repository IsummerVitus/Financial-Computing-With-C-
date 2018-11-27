//
//  main.cpp
//  HW6
//
//  Created by Li M on 15/10/19.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include<vector>
#include<iostream>
#include<assert.h>
using namespace std;
double *spline(double *t,double *r)
{
    double h[3];
    h[0]=t[1]-t[0];h[1]=t[2]-t[1];h[2]=t[3]-t[2];
    double d[3]={0,(r[2]-r[1])/h[1]-(r[1]-r[0])/h[0],(r[3]-r[2])/h[2]-(r[2]-r[1])/h[1]};
    double b[]={0,2*(h[0]+h[1]),2*(h[1]+h[2])};
    double a[]={0,0,h[1]};
    double c[]={0,h[1],0};
    double c1=c[1]/b[1];
    //double c2=c[2]/(b[2]-c1*a[1]);
    double d1=d[1]/b[1];
    double d2=(d[2]-d1*a[2])/(b[2]-c1*a[2]);
    double m[4]={0,d1-c1*d2,d2,0};
    double *z=new double[12];
    assert(z!=NULL);
    
    for(int i=0;i<3;i++)
    {
        z[i]=r[i];z[i+3]=(r[i+1]-r[i])/h[i];z[i+6]=m[i]/2;z[i+9]=(m[i+1]-m[i])/(6*m[i]);
    }
        
    return z;// interpolation with every 4 points and then extrapolation to get the points we need to calculate the rate of next date.
    
}
double extra(double r,double f,double t,double a)
{
    double r1=(r*t+f*a)/(t+a); //according to the assumption that the forward rate will be constant
    return r1;
}

double crate(double *a,double *b,double *c,double *d,double *rate1,double t0)
{
    int i1;double r0;
    double maturity[10]={0.0795,0.2521,0.5014,0.9425,1.9836,3.0247,4.9863,6.9863,9.8630,29.877};
    if(t0>=0.0795&&t0<0.2521)
        i1=0;
    else if(t0<0.5014&&t0>=0.2521)
        i1=1;
    else if (t0>=0.5014&&t0<0.9425)
        i1=2;
    else if (t0>=0.9425&&t0<1.9836)
        i1=3;
    else if (t0>=1.9836&&t0<3.0247)
        i1=4;
    else if (t0>=3.0247&&t0<4.9863)
        i1=5;
    else if (t0>=4.9863&&t0<6.9863)
        i1=6;
    else if (t0>=6.9863&&t0<9.8630)
        i1=7;
    else if (t0>=9.9863&&t0<29.877)
        i1=8;
    else
    {
        double f=(rate1[9]*maturity[9]-rate1[8]*maturity[8])/(maturity[9]-maturity[8]);
        double g=t0-maturity[9];
        r0=extra(rate1[9],f,maturity[9],g);
    }
    r0=a[i1]+b[i1]*(t0-maturity[i1])+c[i1]*sqrt(t0-maturity[i1])+d[i1]*pow((t0-maturity[i1]),3.0);
    return r0;
}


int main()
{
    double rate[10];
    double maturity[10]={0.0795,0.2521,0.5014,0.9425,1.9836,3.0247,4.9863,6.9863,9.8630,29.877};
    double dprice[10]={100,100,99.96,99.77,100.002,99.85,100.0764,100.0537,99.7380,100.1941};//dirty price
    double coupon[10]={0,0,0,0,0.3125,0.4375,0.6875,0.875,1,1.4375};  //semi coupon
    rate[0]=0; rate[1]=0; rate[2]=log(100/dprice[2])/maturity[2]; rate[3]=log(100/dprice[3])/maturity[3];
    double t[4];
    for (int i=0;i<4;i++)
    {
        t[i]=maturity[i];
    }

    double r[4]={rate[0],rate[1],rate[2],rate[3]};
    double *z=spline(t,r);
    double a[9];double b[9];
    double c[9];double d[9];
    for (int i=0;i<3;i++)
    {
        a[i]=z[i];b[i]=z[i+3];
        c[i]=z[i+6];d[i]=z[i+9];
        
    }
    //for time 3/30/16,9/30/16,3/30/17
    double t2[4]={1.9836-1.5,1.9836-1,1.9836-0.5,1.9836};
    double r1=a[1]+b[1]*(t2[0]-t[1])+c[1]*sqrt(t2[0]-t[1])+d[1]*pow((t2[0]-t[1]),3.0);
    double f=(r[3]*t[3]-r[2]*t[2])/(t[3]-t[2]);
    double a2=t2[1]-t[3];double a3=t2[2]-t[3];
    double r2=extra(r[3],f,t[3],a2);
    double r3=extra(r[3],f,t[3],a3);
    rate[4]=log((100+coupon[4])/(dprice[4]-coupon[4]*(exp(-r1*t2[0])+exp(-r2*t2[1])+exp(-r3*t2[2]))))*(1/t2[3]);
    for(int i=5;i<10;i++)
    {
        //double t[4];
        for (int j=i-4;j<i;j++)
        {
            t[j]=maturity[j];
        }
        
        double R[4]={rate[i-4],rate[i-3],rate[i-2],rate[i-1]};
        double *Z=spline(t,R);
        a[i-2]=Z[2];b[i-2]=Z[5];
        c[i-2]=Z[8];d[i-2]=Z[11];
        int k=(static_cast<int>(maturity[i])+0.5)/0.5;
        double *T=new double[k];
        double *R1=new double[k];
        double l=dprice[i];
        for (int m=0;m<k;m++)
        {
            T[m]=maturity[i]-0.5*(k-1-m);
            for(int v=0;v<i-1;v++)
            {
                if (maturity[v]<T[m]&&T[m]<maturity[v+1])
                {
                    R1[m]=a[v]+b[v]*(T[m]-maturity[v])+c[v]*sqrt(T[m]-maturity[v])+d[v]*pow((T[m]-maturity[v]),3.0);
                    if(abs(R1[m])>0.1)
                        R1[m]=0;
                    break;
                }
                
                
            }
            if (T[m]>maturity[i-1])
            {
                double f=(rate[i-1]*maturity[i-1]-rate[i-2]*maturity[i-2])/(maturity[i-1]-maturity[i-2]);
                double g=T[m]-maturity[i-1];
                R1[m]=extra(rate[i-1],f,maturity[i-1],g);
                if(abs(R1[m])>0.1)  //elimiate the abnormal point resulted from constant forward rate assumption
                    R1[m]=0;
                
                
                
            }
            //cout<<R1[m]<<" "<<T[m]<<endl;
            l=l-coupon[i]*exp(-R1[m]*T[m]);
            
            
        }
        rate[i]=log((100+coupon[i])/l)*(1/maturity[i]);
        //cout<< rate[i]<<" "<<k;

        //cout<< rate[i];
        
    }
    for(int i=0;i<10;i++)
        cout<<i<<"-th spot rate is :"<<rate[i]<<endl;
    //cout<<endl;
    double t0;double R2,R3;double T0;double F1;
    cout<<"please input a time t:"<<endl;
    cin>>t0;
    R2=crate(a,b,c,d,rate,t0);
    cout<<"the rate at time t0 is:"<<R2<<endl;
    cout<<"please input the forward period:"<<endl;
    cin>>T0;
    R3=crate(a,b,c,d,rate,t0+T0);
    F1=R3*((t0+T0)-R2*t0)/T0;
    cout<<"the forward rate between t0 and (t0+T0)is: "<<F1;
    
   
 }














