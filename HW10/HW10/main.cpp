//
//  main.cpp
//  HW10
//
//  Created by Li M on 15/11/19.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#include <iostream>
#include "CRR_Tree.h"
int main()
{
    CRRtree tree1(100,0.01,100,0.2,1,20);
    
    cout<<tree1.getprice_zeropruning()<<endl;
    cout<<tree1.getprice_intrinsic()<<endl;
     cout<<tree1.getprice_linear()<<endl;
    cout<<tree1.pricing_RichardsonExtrapolation()<<endl;
    
    
}



