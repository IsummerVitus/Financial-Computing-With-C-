//
//  CrankNicolson.h
//  
//
//  Created by Li M on 15/12/18.
//
//

#ifndef ____CrankNicolson__
#define ____CrankNicolson__

#include <stdio.h>
#include <ctime>
#include <assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include<vector>
#include <algorithm>
using namespace std;

class CrankNicolson{
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
    //vector<vector<double> > S;//store stock price
    vector<vector<double> > P; //store option price
    CrankNicolson(vector<double>vl,vector<double> sl,double price_, double K_, double T_,double vol_, double rate_, int M_, int N_);
    double p();
    double Max(double a,double b);
        
};




#endif /* defined(____CrankNicolson__) */
