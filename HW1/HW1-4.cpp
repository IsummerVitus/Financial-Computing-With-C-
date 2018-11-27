//
//  main.cpp
//  hw1-3
//
//  Created by Li M on 15/9/6.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include <cmath>
#include <iostream>
using namespace std;
int main(void)
{
    double x,value=1,n=1,k=1,temp=0;
    cout<<"please input a real number x:";
    cin>> x;
    do
        {
            temp=pow(x,n)/k;
            value+=temp;
            ++n;
            k=k*n;
        }
    while(temp>=10e-3);
    cout<<"e^x="<<value<<'\t'<<"n="<<n<<endl;
}
    
