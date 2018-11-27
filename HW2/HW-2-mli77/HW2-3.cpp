//
//  main.cpp
//  HW-2-3
//
//  Created by Li M on 15/9/15.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#include <iostream>
#include<vector>
#include<math.h>
using namespace std;
int main()
{
    double c,r,P; int N;int n=1;
    cout<<"Please input the interest rate r:";
    cin>>r;
    cout<<"Please input the amount of loan P:";
    cin>>P;
    cout<<"Please input the number of periods N:";
    cin>>N;
    vector<double> iP(N+1);
    vector<double> iB(N+1);
    vector<double> iI(N+1);
    c=P*r*pow((1+r),N)/(pow((1+r),N)-1);
    iB[0]=P;
    while (n<=N)
    {
        iI[n]=r*iB[n-1];
        iP[n]=c-iI[n];
        iB[n]=iB[n-1]-iP[n];
        cout<<n<<"th period, the Interest part is "<<iI[n]<<", the Principal part is "<<iP[n] <<", the Balance is " <<iB[n]<<endl;
        n++;
    }
    
}
    
        
    
    
    
    
    
    
    


