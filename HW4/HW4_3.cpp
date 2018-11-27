//
//  main.cpp
//  try
//
//  Created by Li M on 15/9/27.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;
void chol(double **a, int size)
{
    int j=0;
    a[j][j]=pow(a[j][j],0.5);
    for(int i=j+1;i<size;i++)
    {
        a[i][j]=a[i][j]/a[j][j];
    }
    
    for(int j=1;j<size;j++)
    {
        int sum=0;
        for(int k=0;k<j;k++)
        {
            sum+=pow(a[j][k],2);
        }
        a[j][j]=pow(a[j][j]-sum,0.5);
        for(int i=j+1;i<size;i++)
        {
            int sum1=0;
            for(int k=0;k<j;k++)
            {
                sum1+=a[i][k]*a[j][k];
            }
            
            a[i][j]=a[i][j]/a[j][j]-sum1;
        }
    }
    
}

int main()
{
     int size;
        //chol(p,size);
    cout<<"please input the size of matrix"<<endl;
    cin>>size;
    double** p = new double*[size];
    for (int i = 0; i < size; ++i)
        p[i] = new double[size];
    //double p[3][3]= {{2,-1,0},{-1,2,-1},{0,-1,2}};
    //double *prow[3]={p[0],p[1],p[2]}
    //dpible **p=prows;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            cout<<"please input p[i][j]"<<endl;cin>>p[i][j];
        }
        
    }
chol(p,size);
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<=i;j++)
        {
            cout<<" "<<p[i][j];
        }
        cout<<endl;
    }
    for (int i = 0; i < size; ++i)
        delete [] p[i];
    delete [] p;
}

