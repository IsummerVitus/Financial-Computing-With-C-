//
//  main.cpp
//  HW-2
//
//  Created by Li M on 15/9/14.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include <iostream>
#include<vector>
using namespace std;
int main()
{
    int n,i=0,j=1,flag=0;
    cout<<"please input an integer n:";
    cin>>n;
    vector<int> ia(n);
    while (i<n-1)
    {cout<<"please input an integer among 1~n:";
        cin>>ia[i];
        i++;
    }
    i=0;
    while (j<=n)
    {
        while(i<(n-1)&&!flag)
        {
            if(j==ia[i])
            {flag=1;}
            i++;
        }
        
        if(flag==0)
        {cout<<"The missing number is:"<<j<<endl;}
        j++;flag=0;i=0;
        
    }

}