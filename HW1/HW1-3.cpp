//
//  main.cpp
//  hw1
//
//  Created by Li M on 15/9/4.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include <cmath>
#include <iostream>
using namespace std;
int main() 									// Most important part of the program!
{
    int n;
    double x;
    cout<<"Please input an interger n equal or greater than zero: ";
    cin>> n;
    cout<<"Please input a real number x: ";
    cin>> x;
    cout<<pow(x,n)<<endl;
    cin.get();
    cin.get();
    return 0;
}
