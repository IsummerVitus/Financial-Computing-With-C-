//
//  main.cpp
//  HW10_1
//
//  Created by Li M on 15/11/20.
//  Copyright (c) 2015年 Li M. All rights reserved.
//


#include "CRR_Tree.h"
#include "Trinomimial_Tree.h"
#include "Tian_Tree.h"
#include "BS.h"


int main()
{
    double spot = 100;double strike = 100;double sigma = 0.2;double r = 0.01;double T = 1;
    int steps[5]{100,500,1000,2000,5000};
    
    double BS = BlackScholesCall(spot, strike, sigma, T, r);
    //CRR  tree
    CRRtree* CRR[5];
    double CRRtree_zero[5];
    double CRRtree_intrinsic[5];
    double CRRtree_linear[5];
    for (int i = 0; i < 5; i++)
    {
        CRR[i]= new CRRtree(spot, strike, sigma, r, T, steps[i]);
        CRR[i]->build_Tree();
        CRR[i]->finalprice();
        CRRtree_zero[i] = CRR[i]->getprice_zeropruning();
        CRRtree_intrinsic[i] = CRR[i]->getprice_intrinsic();
        CRRtree_linear[i] = CRR[i]->getprice_linear();
    }
    double CRR_error_zero[5];
    double CRR_error_intrinsic[5];
    double CRR_error_linear[5];
    for (int i = 0; i < 5; i++) {
        CRR_error_zero[i] = CRRtree_zero[i] - BS;
        cout <<i<<"-thCRRerror1"<< CRR_error_zero[i] <<endl;
        CRR_error_intrinsic[i] = CRRtree_intrinsic[i] - BS;
        cout <<i<<"-thCRRerror2"<< CRR_error_intrinsic[i] << endl;
        CRR_error_linear[i] = CRRtree_linear[i] - BS;
        cout <<i<<"-thCRRerror3"<< CRR_error_linear[i] << endl;
    }
    
    // TIan tree
    Tiantree* tian[5];
    double TIAN_setzero[5];
    double TIAN_intrinsic[5];
    double TIAN_linear[5];
    for (int i = 0; i < 5; i++) {
        tian[i] = new Tiantree(spot, strike, sigma, r, T, steps[i]);
        tian[i]->build_Tree();
        tian[i]->finalprice();
        TIAN_setzero[i] = tian[i]->getprice_zeropruning();
        TIAN_intrinsic[i] = tian[i]->getprice_intrinsic();
        TIAN_linear[i] = tian[i]->getprice_linear();
    }
    
    double TIAN_error_setzero[5];
    double TIAN_error_intrinsic[5];
    double TIAN_error_linear[5];
    for (int i = 0; i < 5; i++) {
        TIAN_error_setzero[i] = TIAN_setzero[i] - BS;
        cout <<i<<"-th Tianerror1"<< TIAN_error_setzero[i] << endl;
        TIAN_error_intrinsic[i] = TIAN_intrinsic[i] - BS;
        cout <<i<<"-th Tianerror2"<< TIAN_error_intrinsic[i] << endl;
        TIAN_error_linear[i] = TIAN_linear[i] - BS;
        cout <<i<<"-th Tianerror3"<< TIAN_error_linear[i] << endl;
    }
    //Trinomial tree
    cout << "Trinomial model:" << endl;
    TRI_Tree* TRI[5];
    double TRI_setzero[5];
    double TRI_intrinsic[5];
    double TRI_linear[5];
    for (int i = 0; i < 5; i++) {
        TRI[i] = new TRI_Tree(spot, strike, sigma, r, T, steps[i]);
        TRI[i]->buildTree();
        TRI[i]->finalprice();
        TRI_setzero[i] = TRI[i]->getprice_zeropruning();
        TRI_intrinsic[i] =TRI[i]->getprice_intrinsic();
        TRI_linear[i] = TRI[i]->getprice_linear();
    }
  
    double TRI_error_zero[5];
    double TRI_error_intrinsic[5];
    double TRI_error_linear[5];
    for (int i = 0; i < 5; i++) {
        TRI_error_zero[i] = TRI_setzero[i] - BS;
        cout <<i<<"-th TRIerror1"<< TRI_error_zero[i] << endl;
        TRI_error_intrinsic[i] = TRI_intrinsic[i] - BS;
        cout <<i<<"-th TRIerror1"<<TRI_error_intrinsic[i] << endl;
        TRI_error_linear[i] = TRI_linear[i] - BS;
        cout <<i<<"-th TRIerror1"<< TRI_error_linear[i] << endl;
    }
    
}