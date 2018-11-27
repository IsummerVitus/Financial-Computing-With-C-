//
//  main.cpp
//  HW3_1
//
//  Created by Li M on 15/9/21.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
char * myStrcat(const char*st1,const char* st2)
{
    int i=0;int j=0;
    while (*(st1++)!='\0')
    {
        i++;
    }
    while (*(st2++)!='\0')
    {
        j++;
    }
    
    char *st3=new char[i+j+1];
    i=0;j=0;
    while (*(st1++)!='\0')
    {
        *(st3+i)=*(st1+i);
        i++;
    }
    while (*(st2++)!='\0')
    {
        *(st3+i+j)=*(st2+j);
        j++;
    }
    *(st3+i+j)='\0';
    return st3;
}