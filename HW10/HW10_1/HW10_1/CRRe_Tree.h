//
//  CRR_Tree.h
//  HW10
//
//  Created by Li M on 15/11/19.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#ifndef HW10_CRR_Tree_h
#define HW10_CRR_Tree_h
#include <vector>
#include <math.h>
#include <algorithm>
#include "BS.h"
using namespace std;
class CRRtree
{
public:
    CRRtree(double spot_,const double r_, double strike_,
                   double sigma_,double T_,int N_):spot(spot_),r(r_),strike(strike_),
                   sigma(sigma_),T(T_),N(N_)
    {
        dt=T/N;
        u = exp(sigma*sqrt(dt));
        d = exp(-sigma*sqrt(dt));
        pu = (exp(r*dt) - d) / (u - d);
        pd = 1 - pu;
        upper = spot*exp((r - sigma*sigma / 2)*T + 6 * sigma*sqrt(T));
        lower = spot*exp((r - sigma*sigma / 2)*T - 6 * sigma*sqrt(T));
        //cutstep= min(floor(log(upper/spot)/log(u)),floor(log(lower/spot)/log(d)));
        call1.resize(N);
        call2.resize(N);
        
    }
    double getprice_zeropruning();
    double getprice_intrinsic();
    double getprice_linear();int cutstep;double upper; double lower;double u;double d;
    double pricing_RichardsonExtrapolation();
private:
    double spot;const double r;double sigma;double T;int N;double dt;
    vector<double> call1;
    vector<double> call2;
    vector<double> stock;
    double pu; double pd; double strike;
    
protected:
    void buildtree();
    void finalprice();
    double pricing();
    
    
};
void CRRtree::finalprice()
{
    call1.resize(N+1);
    for(int i=0;i<=N;i++)
    {call1[i]=fmax(0,pow(d,N-i)*pow(u,i)*spot-strike);}
    call2.resize(N);
    for(int i=0;i<N;i++)
    {
        call2[i]=(call1[i+1]*pu+call1[i]*pd)*exp(-r*dt);
    }

}  //call2 is the current opition price and call1 is the future opition price

double CRRtree::pricing()
{
    for(int j=N-1;j>=0;j--)
    {
        call1.resize(j+1);
        for(int i=0;i<=j;i++)
        {
            call1[i]=call2[i];
        }
        call2.resize(j);
        for(int i=0;i<j;i++)
        {
            call2[i]=(call1[i+1]*pu+call1[i]*pd)*exp(-r*dt);
        }
        
    }
    return call2[0];
}

double CRRtree::getprice_zeropruning()  //get the option price at i-th step
{
    call1.resize(N+1);
    for(int i=0;i<=N;i++)
            {
                call1[i]=fmax(0,pow(d,N+1-i)*pow(u,i)*spot-strike);
            }

    for (int i = N-1; i >= 0; i--)
    {
        call2.resize(i+1);
        for (int j = 0; j <=i ; j++)
        {
            if (spot*pow(u,j)*pow(d,i-j)>=lower&&spot*pow(u,j)*pow(d,i-j)<= upper) {
                call2[j] = (call1[i+1]*pu+call1[i]*pd)*exp(-r*dt);
            }
            else {
                call2[j]= 0;
            }
            
        }
        call1=call2;
    }
    return call2[0];
}
//    vector<double>temp;
//    
//    call1.resize(cutstep+1);
//    temp.resize(N+1);
//    for(int i=0;i<=N;i++)
//    {
//        temp[i]=fmax(0,pow(d,N+1-i)*pow(u,i)*spot-strike);
//    }
//    for(int i=0;i<=cutstep;i++)
//    {
//        int d=ceil((N-cutstep)/2);
//        call1[i]=temp[i+d];
//    }
//    call2.resize(cutstep);
//    for (int i=0; i<=cutstep-1; i++) {
//        call2[i]=(call1[i+1]*pu+call1[i]*pd)*exp(-r*dt);
//    }
//    for(int j=N-2;j>=cutstep;j--)
//    {
//        call1.resize(cutstep+1);
//        call1[cutstep]=0;call1[0]=0;
//        for(int i=1;i<=cutstep-1;i++)
//        {
//            call1[i]=(call2[i]*pu+call2[i-1]*pd)*exp(-r*dt);
//        }
//        j--;
//        call2.resize(cutstep);
//        for(int i=0;i<=cutstep-1;i++)
//        {
//            call2[i]=(call1[i+1]*pu+call1[i]*pd)*exp(-r*dt);
//        }
//        
//    }
//    for(int j=cutstep;j>=0;j--)
//    {
//        call1.resize(j+1);
//        for(int i=0;i<=j;i++)
//        {
//            call1[i]=call2[i];
//        }
//        call2.resize(j);
//        for(int i=0;i<j;i++)
//        {
//            call2[i]=(call1[i+1]*pu+call1[i]*pd)*exp(-r*dt);
//        }
//        
//    }
//    return call2[0];
//}
//








double CRRtree::getprice_intrinsic()  //get the option price at i-th step
{
    call1.resize(cutstep+2);
    for(int i=0;i<=cutstep+1;i++)
    {call1[i]=fmax(0,pow(d,cutstep+1-i)*pow(u,i)*spot-strike);}
    call2.resize(cutstep+1);
    call2[cutstep]=fmax(0, spot-strike*exp(-r*(T-cutstep*dt)));
    call2[0]=fmax(0, spot-strike*exp(-r*(T-cutstep*dt)));
    for(int i=1;i<cutstep;i++)
    {
        call2[i]=(call1[i+1]*pu+call1[i]*pd)*exp(-r*dt);
    }  ///calculate the last two opition price vectors
    for(int j=cutstep;j>=0;j--)
    {
        call1.resize(j+1);
        for(int i=0;i<=j;i++)
        {
            call1[i]=call2[i];
        }
        call2.resize(j);
        for(int i=0;i<j;i++)
        {
            call2[i]=(call1[i+1]*pu+call1[i]*pd)*exp(-r*dt);
        }
        
    }
    return call2[0];
}

double CRRtree::getprice_linear()  //get the option price at i-th step
{
    call1.resize(cutstep+2);
    for(int i=0;i<=cutstep+1;i++)
    {call1[i]=fmax(0,pow(d,cutstep+1-i)*pow(u,i)*spot-strike);}
    call2.resize(cutstep+1);
    for(int i=0;i<cutstep+1;i++)
    {
        call2[i]=(call1[i+1]*pu+call1[i]*pd)*exp(-r*dt);
    }
    for(int j=cutstep;j>=0;j--)
    {
        call1.resize(j+1);
        for(int i=0;i<=j;i++)
        {
            call1[i]=call2[i];
        }
        call2.resize(j);
        for(int i=0;i<j;i++)
        {
            call2[i]=(call1[i+1]*pu+call1[i]*pd)*exp(-r*dt);
        }
        
    }
    return call2[0];
}
double CRRtree::pricing_RichardsonExtrapolation()
{
    
    CRRtree CRR1(spot,r, strike, sigma, T, N);
    CRR1.finalprice();
    CRRtree CRR2(spot,r, strike, sigma, T, N/2);
    CRR2.finalprice();
    
    
    double p_bsm = BlackScholesCall(spot,strike,sigma,T,r);
    double k = 2.001907;
    double p = (k*CRR1.pricing() - CRR2.pricing()) / (k - 1);
    
    //double error = (CRR2.pricing() - p_bsm) / (CRR1.pricing() - p_bsm);
    cout<<p_bsm;
    return p;
    
}














#endif
