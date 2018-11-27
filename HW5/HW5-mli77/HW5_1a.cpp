//
//  main.cpp
//  HW5_1a
//
//  Created by Li M on 15/10/5.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#include<iostream>
#include<math.h>
using namespace std;
double payoff(double K,double S)
{
    double a;
    if (S>K)
        a=S-K;
    else
        a=0;
    return a;
}
