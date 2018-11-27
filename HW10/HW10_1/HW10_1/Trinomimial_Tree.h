#pragma once
#include "CRR_Tree.h"

class TRI_Tree
{
private:
    double u;
    double d;
    double pu;
    double pm;
    double pd;
	double spot;
	double strike;
	double sigma;
	double r;
    double T;double upper; double lower;
	int N;double delta_t;
	vector<vector<pair<double, double>>> Tree;
public:
	TRI_Tree() {};

	TRI_Tree(double spot_, double r_,double strike_,double sigma_,  double T_, int N_) :
		spot(spot_),  sigma(sigma_), r(r_), strike(strike_),T(T_), N(N_)
	{
		delta_t = T / N;
		u = exp(sigma*sqrt(delta_t));
		d = 1 / u;
		double R = exp(r*delta_t);
		double S = R*R*sigma*sigma*delta_t;
		pu = ((S + R*R - R)*u - (R - 1)) / (u - 1) / (u*u - 1);
		pm = (R*u*u - (S + R*R + 1)*u + R) / (u - 1) / (u - 1);
		pd = (S + R*R - R - R*u + u)*u*u / (u - 1) / (u*u - 1);
        upper = spot*exp((r - sigma*sigma / 2)*T + 6 * sigma*sqrt(T));
        lower = spot*exp((r - sigma*sigma / 2)*T - 6 * sigma*sqrt(T));
	}

	~TRI_Tree()
	{
		for (int i = 0; i < static_cast<int>( Tree.size()); i++)
		{
			Tree[i].clear();
		}
		Tree.clear();
	}

	void buildTree()
	{
		Tree.resize(N + 1);
		for (int i = 0; i < N + 1; i++)
		{
			Tree[i].resize(2*i+1);
		}

		Tree[0][0].first = spot;
		for (int i = 1; i < N + 1; i++)
		{
			for (int j = 0; j <static_cast<int>( Tree[i].size())-2; j++)
			{
				Tree[i][j].first =d*Tree[i - 1][j].first;
			}
			Tree[i][2 * i - 1].first = Tree[i - 1][2 * i - 2].first;
			Tree[i][2*i].first = u*Tree[i-1][2*i-2].first;
		}
	}

	void finalprice()
	{
		for (int i = 0; i < static_cast<int>(Tree[N].size()); i++)
		{
			Tree[N][i].second = max(0.0, Tree[N][i].first - strike);
		}
	}

	double pricing()
	{
		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = 0; j < static_cast<int>(Tree[i].size()); j++)
			{
				Tree[i][j].second = exp(-r*delta_t)*(pu*Tree[i + 1][j + 2].second + pm*Tree[i + 1][j+1].second+pd*Tree[i+1][j].second);
			}
		}

		return Tree[0][0].second;
	}

	double getprice_zeropruning()
	{
		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = 0; j < static_cast<int>(Tree[i].size()); j++)
			{
				if (Tree[i + 1][j].first >=lower&&Tree[i + 1][j + 2].first <= upper) {
					Tree[i][j].second = exp(-r*delta_t)*(pu*Tree[i + 1][j + 2].second + pm*Tree[i + 1][j + 1].second + pd*Tree[i + 1][j].second);
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
            for (int j = 0; j < static_cast<int>(Tree[i].size()); j++)
            {
                if (Tree[i + 1][j].first >=lower&&Tree[i + 1][j + 2].first <= upper) {
                    Tree[i][j].second = exp(-r*delta_t)*(pu*Tree[i + 1][j + 2].second + pm*Tree[i + 1][j + 1].second + pd*Tree[i + 1][j].second);
                }
                else {
					Tree[i][j].second = max(spot - strike*exp(-r*delta_t*(N - i)), 0.0);
				}

			}
		}

		return Tree[0][0].second;

	}


	double getprice_linear()
	{
        for (int i = N - 1; i >= 0; i--)
        {
            for (int j = 0; j < static_cast<int>(Tree[i].size()); j++)
            {
                if (Tree[i + 1][j].first >=lower&&Tree[i + 1][j + 2].first <= upper) {
                    Tree[i][j].second = exp(-r*delta_t)*(pu*Tree[i + 1][j + 2].second + pm*Tree[i + 1][j + 1].second + pd*Tree[i + 1][j].second);
                }
                else {
					Tree[i][j].second = (Tree[i + 1][j].second+Tree[i+1][j+1].second+Tree[i+1][j+2].second)/3;
				}

			}
		}

		return Tree[0][0].second;

	}


	double pricing_RichardsonExtrapolation()
	{

		TRI_Tree Tree1(spot, strike, sigma, r, T, N);
		Tree1.buildTree();
		Tree1.finalprice();

		TRI_Tree Tree2(spot, strike, sigma, r, T, N / 2);
		Tree2.buildTree();
		Tree2.finalprice();

		double k=1.0049;

		double p = (pow(2, k)*Tree1.pricing() - Tree2.pricing()) / (pow(2, k) - 1);

		return p;

	}





};
