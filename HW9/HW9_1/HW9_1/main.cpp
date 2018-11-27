//
//  main.cpp
//  HW9_1
//
//  Created by Li M on 15/11/10.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#include "Matrix.h"
int main()
{
    Matrix bMatrix(3, 3);
    cout<<"please input number for your matrix:"<<endl;
    cin >> bMatrix;
    
    cout <<"the matrix you input is:"<<endl<< bMatrix;
    bMatrix.inverse();
    cout<< bMatrix;
    
    //bMatrix.LUDecompose();
    
    vector<double> c
    
    
    vector<double> b{ 10,12,15 };
    
    cout<<"After GaussSeidl"<<endl;
    bMatrix.GaussSeidel(b, 100);
    
    
    cin.get();
    return 0;
    
}