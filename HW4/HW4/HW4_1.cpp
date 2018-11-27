//
//  main.cpp
//  HW4_1
//
//  Created by Li M on 15/9/27.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include<iostream>
#include<string>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <assert.h>
using namespace std;
char * stringReverse(const char *st) // allocates a new string, no manipulations on st
{
    int i=0;
    while (*(st++)!='\0')
        i++;
    st-=i+1;
    char *array=new char[i];
    assert(array!=NULL);
    for(int j=0;j<i;j++)
    {
        array[j]=st[i-1-j];
    }
    return array;
}
void display(int* ar,int size)
{
    for(int i=0;i<size;i++)
        cout<<" "<<ar[i];
    cout<<endl;
}

void input(int* ar,int size)
{
    for(int i=0;i<size;i++)
    {
        cin>>ar[i];
        
    }
}

int main()
{
    const char* ar="Hello world";
    int size=0;
    while (*(ar++)!='\0')
        size++;
    ar-=size+1;
    //cout<<"The length of: "<<ar<<" is "<<size<<endl;
    char* p=stringReverse(ar);
    for(int i=0;i<size;i++)
        cout<<" "<<*(p++);
    cout<<endl;
    delete [] p;
}