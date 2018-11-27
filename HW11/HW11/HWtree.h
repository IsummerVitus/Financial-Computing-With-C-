//
//  HWtree.h
//  HW11
//
//  Created by Li M on 15/12/1.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#ifndef HW11_HWtree_h
#define HW11_HWtree_h
#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

class HWtree
{
private:
    double delta_R;double theta;double a;double delta_t;double T;int N;
    int jmax; int jmin;double *rate;
    vector<vector<double>> Tree;   //store short rate
    vector<vector<double>> Q;  //store Q
    vector<double> alpha;
    vector<double> p;
    vector<double> Pu; double *pu;
    vector<double> Pm; double *pm;
    vector<double> Pd; double *pd;
public:
    HWtree() {};
    
    HWtree(double T_,int N_,double theta_,double a_,double *Rate) :
    T(T_),N(N_),theta(theta_),a(a_)
    {
        delta_t=T/N;
        delta_R=theta*sqrt(3*delta_t);
        jmax = ceil(0.184 / a / delta_t);
        jmin = -jmax;
        for (int i=0;i<N;i++)
        {
            rate = new double[N];
            for (int i=0; i<N; ++i) {
                rate[i] = Rate[i];
            }

           
        }
        Pu.resize(2 * jmax + 1); pu = &Pu[jmax];
        Pm.resize(2 * jmax + 1); pm = &Pm[jmax];
        Pd.resize(2 * jmax + 1); pd = &Pd[jmax];
    }
    
    ~HWtree()
    {
        for (int i = 0; i < static_cast<int>(Tree.size()); i++)
        {
            Tree[i].clear();Q[i].clear();
        }
        Tree.clear();
        Q.clear();
    }
    
    void buildtree()
    {
        Tree.resize(N + 1);Q.resize(N+1);
        alpha.resize(N+1);alpha[0]=rate[0];
        p.resize(N+1);
        for (int i = 0; i < N + 1; i++)
        {
            Tree[i].resize(2*jmax+1);
            Q[i].resize(2*(jmax+1)+1);
        }
        
        Tree[0][0+jmax]= 0;Q[0][0+jmax]=1;
        for (int i = 0; i <N+1; i++){
            if (i <= jmax) {
                for (int j = -i; j <= i; j++) {
                    Tree[i][j+jmax] = j*delta_R;
                }
            }
            else {
                for (int j = jmin; j <= jmax; j++) {
                    Tree[i][j+jmax] = j*delta_R;
                }
            }
        }
        for (int j = jmin; j <= jmax; j++) {
            if (j == jmin) {
                pu[j] = 1.0 / 6.0 + 0.5*(pow(a,2)*pow(j,2)*pow(delta_t,2) + a*j*delta_t);
                pm[j] = -1.0 / 3.0 - pow(a,2)*pow(j,2)*pow(delta_t,2) - 2 * a*j*delta_t;
                pd[j] = 7.0 / 6.0 + 0.5*(pow(a,2)*pow(j,2)*pow(delta_t,2) + 3 * a*j*delta_t);
            }
            else if (j > jmin&&j < jmax) {
                pu[j] = 1.0 / 6.0 + 0.5*(pow(a,2)*pow(j,2)*pow(delta_t,2) - a*j*delta_t);
                pm[j] = 2.0 / 3.0 - pow(a,2)*pow(j,2)*pow(delta_t,2);
                pd[j] = 1.0 / 6.0 + 0.5*(pow(a,2)*pow(j,2)*pow(delta_t,2) + a*j*delta_t);
            }
            else if (j == jmax) {
                pu[j] = 7.0 / 6.0 + 0.5*(pow(a,2)*pow(j,2)*pow(delta_t,2) -3* a*j*delta_t);
                pm[j] = -1.0 / 3.0 - pow(a,2)*pow(j,2)*pow(delta_t,2) + 2 * a*j*delta_t;
                pd[j] = 1.0 / 6.0 + 0.5*(pow(a,2)*pow(j,2)*pow(delta_t,2) - a*j*delta_t);
            }
        }
        
    }
    void buildHWtree()
    {
       
        for (int i=0;i<N;)
        {
            
            if(i==1)
            {
                cout<<"Q1:"<<Q[0][jmax]<<" "<<Q[i][i+jmax]<<" "<<Q[i][i-1+jmax]<<" "<<Q[i][-1+jmax]<<endl;;
            }
           
            
            
            if (i<jmax)
            {
                for (int j = -i-1; j <= i+1; j++)
                {
                    Q[i+1][j+jmax]= Q[i][j - 1+jmax] * pu[j - 1] * exp(-(alpha[i] + (j - 1)*delta_R)*delta_t)
                    + Q[i][j+jmax] * pm[j] * exp(-(alpha[i] + (j)*delta_R)*delta_t)
                    + Q[i][j + 1+jmax] * pd[j + 1] * exp(-(alpha[i] + (j + 1)*delta_R)*delta_t);
                }
            }
            
            else if (i >=jmax)
            {
                for (int j = jmin+3; j <= jmax-3; j++)
                {
                    Q[i + 1][j+jmax] += Q[i][j - 1+jmax] * pu[j - 1] * exp(-(alpha[i] + (j - 1)*delta_R)*delta_t);
                    Q[i + 1][j+jmax] += Q[i][j+jmax] * pm[j] * exp(-(alpha[i] + (j)*delta_R)*delta_t);
                    Q[i + 1][j+jmax] += Q[i][j + 1+jmax] * pd[j + 1] * exp(-(alpha[i] + (j + 1)*delta_R)*delta_t);
                }
                
                
                Q[i + 1][jmin+jmax] = Q[i][jmin+jmax] * pd[-jmax] * exp(-(alpha[i] + jmin*delta_R)*delta_t)
					           + Q[i][jmin + 1] * pd[jmin + 1] * exp(-(alpha[i] + (jmin + 1)*delta_R)*delta_t);
                
                Q[i + 1][jmin+1+jmax] = Q[i][jmin+jmax] * pm[jmin] * exp(-(alpha[i] + jmin*delta_R)*delta_t)
                + Q[i][jmin + 1+jmax] * pm[jmin + 1] * exp(-(alpha[i] + (jmin + 1)*delta_R)*delta_t)
                + Q[i][jmin + 2+jmax] * pd[jmin + 2] * exp(-(alpha[i] + (jmin + 2)*delta_R)*delta_t);
                
                Q[i + 1][jmin+2+jmax] = Q[i][jmin+jmax] * pu[jmin] * exp(-(alpha[i] + jmin*delta_R)*delta_t)
                + Q[i][jmin + 1+jmax+jmax] * pu[jmin + 1] * exp(-(alpha[i] + (jmin + 1)*delta_R)*delta_t)
                + Q[i][jmin + 2+jmax] * pm[jmin + 2] * exp(-(alpha[i] + (jmin + 2)*delta_R)*delta_t)
                + Q[i][jmin + 3+jmax] * pd[jmin + 3] * exp(-(alpha[i] + (jmin + 3)*delta_R)*delta_t);
                
                Q[i + 1][jmax+jmax] = Q[i][jmax] * pu[jmax] * exp(-(alpha[i] + jmax*delta_R)*delta_t)
					           + Q[i][jmax - 1] * pu[jmax - 1] * exp(-(alpha[i] + (jmax - 1)*delta_R)*delta_t);
                
                Q[i + 1][jmax - 1+jmax] = Q[i][jmax+jmax] * pm[jmax] * exp(-(alpha[i] + jmax*delta_R)*delta_t)
                + Q[i][jmax - 1+jmax] * pm[jmax - 1] * exp(-(alpha[i] + (jmax - 1)*delta_R)*delta_t)
                + Q[i][jmax - 2+jmax] * pu[jmax - 2] * exp(-(alpha[i] + (jmax - 2)*delta_R)*delta_t);
                
                Q[i + 1][jmax - 2+jmax] = Q[i][jmax+jmax] * pd[jmax] * exp(-(alpha[i] + jmax*delta_R)*delta_t)
                + Q[i][jmax - 1+jmax] * pd[jmax - 1] * exp(-(alpha[i] + (jmax - 1)*delta_R)*delta_t)
                + Q[i][jmax - 2+jmax] * pm[jmax - 2] * exp(-(alpha[i] + (jmax - 2)*delta_R)*delta_t)
                + Q[i][jmax - 3+jmax] * pu[jmax - 3] * exp(-(alpha[i] + (jmax - 3)*delta_R)*delta_t);
                
                
                if (jmax == 2)
                {
                    Q[i + 1][0+jmax] = Q[i+1][0+jmax]-Q[i][-1+jmax] * pu[-1] * exp(-(alpha[i] + (-1)*delta_R)*delta_t)
                    - Q[i][0+jmax] * pm[-0] * exp(-(alpha[i] + (0)*delta_R)*delta_t)
                    - Q[i][1+jmax] * pd[1] * exp(-(alpha[i] + (1)*delta_R)*delta_t);
                }
            }
            i++;
            p[i+1]=exp(-rate[i+1]*(i+1)/delta_t);
            double s=0;
            for(int j=jmin;j<jmax+1;j++)
            {
                s+=Q[i][j+jmax]*exp(-j*delta_R*delta_t);
            }
            alpha[i]=(log(s)-log(p[i+1]))/delta_t;
        }
        for (int i = 1; i < N + 1; i++)
        {
            for (int j = jmin; j < jmax+1; j++)
            {
                Tree[i][j+jmax]+=alpha[i];
            }
        }

    }
    


    
    void print_Tree()
    {
        cout<<"alpha is: "<<endl;
        for(int i=0;i<N;i++)
        {
            cout<< " "<<alpha[i];
        }
        cout<<endl;
        cout << "The tree is:" << endl;
        for (int i = 0; i < static_cast<int>(Tree.size())-1; i++)
        {
            for (int j = jmin; j < jmax+1; j++)
            {
                cout << " "<<Tree[i][j+jmax];
            }
            cout << endl;
        }
        return;
    }
};

    
    
    
    
    
    
    
    
    
    
    
    
    
    


                
                
        

                
             
               
        
                
                
        
                
                
        
        
        
        
        
        
        

 




#endif
