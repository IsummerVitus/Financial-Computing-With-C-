//  CRR_Tree.h
//  HW10
//
//  Created by Li M on 15/11/19.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#ifndef HW10_CRR_Tree_h
#define HW10_CRR_Tree_h
#include <vector>
#include <math.h>
#include <algorithm>
#include "BS.h"
using namespace std;


class CRRtree
{
private:
	double spot;double strike;double sigma;
	double r;double T;int N;double dt;
    double u;double d;double pu;double pd;double upper; double lower;
	vector<vector<pair<double, double>>> Tree;
public:
	CRRtree() {};

    CRRtree(double spot_,double r_, double strike_,
            double sigma_,double T_,int N_):spot(spot_),r(r_),strike(strike_),sigma(sigma_),T(T_),N(N_)
	{
		dt = T / N;
		u = exp(sigma*sqrt(dt));
		d = exp(-sigma*sqrt(dt));
		pu = (exp(r*dt) - d) / (u - d);
		pd = 1 - pu;
        upper = spot*exp((r - sigma*sigma / 2)*T + 6 * sigma*sqrt(T));
        lower = spot*exp((r - sigma*sigma / 2)*T - 6 * sigma*sqrt(T));
        

	}

	~CRRtree()
	{
		for (int i = 0; i < static_cast<int>(Tree.size()); i++)
		{
			Tree[i].clear();
		}
		Tree.clear();
	}

	void build_Tree()
	{
		Tree.resize(N + 1);
		for (int i = 0; i < N + 1; i++)
		{
			Tree[i].resize(i + 1);
		}

		Tree[0][0].first = spot;
		for (int i = 1; i < N + 1; i++)
		{
			for (int j = 0; j < i; j++)
			{
				Tree[i][j].first = d*Tree[i - 1][j].first;
			}
			Tree[i][i].first = u*Tree[i - 1][i - 1].first;
		}
	}

	void finalprice()
	{
		for (int i = 0; i < ceil(Tree[N].size()); i++)
		{
			Tree[N][i].second = max(0.0, Tree[N][i].first - strike);
		}
	}

	double pricing()
	{
		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = 0; j < ceil(Tree[i].size()); j++)
			{
				Tree[i][j].second = exp(-r*dt)*(pu*Tree[i + 1][j + 1].second +
                                                     pd*Tree[i + 1][j].second);
			}
		}

		return Tree[0][0].second;
	}

	double getprice_zeropruning()
	{

		for (int i = N - 1; i >= 0; i--)
		{
            for (int j = 0; j < ceil(Tree[i].size()); j++)
			{
				if (Tree[i + 1][j].first >= lower&&Tree[i + 1][j + 1].first <= upper) {
					Tree[i][j].second = exp(-r*dt)*(pu*Tree[i + 1][j + 1].second + pd*Tree[i + 1][j].second);
				}
				else {
					Tree[i][j].second = 0;
				}

			}
		}

		return Tree[0][0].second;

	}


	double getprice_intrinsic()
	{

		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = 0; j < ceil(Tree[i].size()); j++)
			{
				if (Tree[i + 1][j].first >= lower&&Tree[i + 1][j + 1].first <= upper) {
					Tree[i][j].second = exp(-r*dt)*(pu*Tree[i + 1][j + 1].second + pd*Tree[i + 1][j].second);
				}
				else {
					Tree[i][j].second = max(spot - strike*exp(-r*dt*(N - i)), 0.0);
				}

			}
		}

		return Tree[0][0].second;

	}

	double getprice_linear()
	{

		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = 0; j < ceil(Tree[i].size()); j++)
			{
                if (Tree[i + 1][j].first >= lower&&Tree[i + 1][j + 1].first <= upper) {
                    Tree[i][j].second = exp(-r*dt)*(pu*Tree[i + 1][j + 1].second + pd*Tree[i + 1][j].second);
                }
                else {
					Tree[i][j].second = 0.5*Tree[i + 1][j + 1].second + 0.5*Tree[i + 1][j].second;
				}

			}
		}

		return Tree[0][0].second;

	}


	double pricing_RichardsonExtrapolation()
	{
		
		CRRtree CRR1(spot, strike, sigma, r, T, N);
		CRR1.build_Tree();
		CRR1.finalprice();

	
		CRRtree CRR2(spot, strike, sigma, r, T, N/2);
		CRR2.build_Tree();
		CRR2.finalprice();


		//double p_bsm = BlackScholesCall(spot,strike,sigma,T,r);
		double k = 2.001907;
		double p = (k*CRR1.pricing() - CRR2.pricing()) / (k - 1);

		//double error = (CRR2.pricing() - p_bsm) / (CRR1.pricing() - p_bsm);

		return p;
		
	}


};













#endif
