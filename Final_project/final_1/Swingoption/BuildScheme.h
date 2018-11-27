//
//  BuildScheme.h
//  Swingoption
//
//  Created by Li M on 15/12/18.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#ifndef __Swingoption__BuildScheme__
#define __Swingoption__BuildScheme__
#include <iostream>
#include <ctime>
#include <assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include<vector>
#include <algorithm>

using namespace std;

class BuildScheme{
private:
    double price; double K; double T;
    vector<double> b;   // vector of Z(i,j)’s
    vector<double> c1;
    vector<double> d;
    vector<double> x;
    
    double dx ;              // state step size
    double drift ;  // drift rate
    double pu, pm, pd;                // risk neutral probabilities
    int i, j;
    double a ;
    double deltat;
    double vol; double rate; double div; int M; int N; char type;
    
public:
    vector<vector<double> > S;//store stock price
    vector<vector<double> > P; //store option price
    BuildScheme(double price_, double K_, double T_,double vol_, double rate_, int M_, int N_);
    double Max(double a,double b);
};



#endif /* defined(__Swingoption__BuildScheme__) */


