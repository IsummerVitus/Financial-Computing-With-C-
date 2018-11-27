//
//  HWTree.h
//  IRofHWTree
//
//  Created by Li M on 15/12/17.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#ifndef HWTREE_H
#define HWTREE_H

#include <vector>

class HWTree
{
public:
    HWTree(std::vector<double> zeroRate,
           double Speed_,
           double Volatility_,
           long Steps_,
           double Time_);
    double bp();
    void printQ();
private:
    double Speed;
    double Volatility;
    long Steps;
    double Time;
    std::vector<std::vector<double>> BP;    // store bond price B(t,t+delta),
    
    std::vector<std::vector<double> > TheTree;
    std::vector<std::vector<double> > r;
    std::vector<std::vector<double> > Q;
};

#endif