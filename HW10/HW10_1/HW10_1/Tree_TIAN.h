#pragma once

#include "Tree_CRR.h"

class BinomialTree_TIAN
{
private:
	double spot;
	double strike;
	double sigma;
	double r;
	double T;
	int N;                    //steps
	double delta_t;

	double u;                  //up  factor
	double d;                  //down factor
	double pu;                 //probability-up
	double pd;                 //probability-down

	vector<vector<pair<double, double>>> Tree_binomial;
public:
	BinomialTree_TIAN() {};

	BinomialTree_TIAN(double spot_, double strike_, double sigma_, double r_, double T_, int N_) :
		spot(spot_), strike(strike_), sigma(sigma_), r(r_), T(T_), N(N_)
	{
		delta_t = T / N;
		double R = exp(r*delta_t);
		double V = exp(pow(sigma, 2)*delta_t);

		u = R*V / 2 * (V + 1 + sqrt(pow(V, 2) + 2 * V - 3));
		d = R*V / 2 * (V + 1 - sqrt(pow(V, 2) + 2 * V - 3));

		pu = (exp(r*delta_t) - d) / (u - d);
		pd = 1 - pu;
	}

	~BinomialTree_TIAN()
	{
		for (int i = 0; i < static_cast<int>(Tree_binomial.size()); i++)
		{
			Tree_binomial[i].clear();
		}
		Tree_binomial.clear();
	}

	void build_BinomialTree()
	{
		Tree_binomial.resize(N + 1);
		for (int i = 0; i < N + 1; i++)
		{
			Tree_binomial[i].resize(i + 1);
		}

		Tree_binomial[0][0].first = spot;
		for (int i = 1; i < N + 1; i++)
		{
			for (int j = 0; j < i; j++)
			{
				Tree_binomial[i][j].first = d*Tree_binomial[i - 1][j].first;
			}
			Tree_binomial[i][i].first = u*Tree_binomial[i - 1][i - 1].first;
		}
	}


	void print_Tree()
	{
		cout << "The tree is:" << endl;
		for (int i = 0; i <static_cast<int>( Tree_binomial.size()); i++)
		{
			for (int j = 0; j <static_cast<int>( Tree_binomial[i].size()); j++)
			{
				cout << Tree_binomial[i][j].first << "(" << Tree_binomial[i][j].second << ")" << "    ";
			}
			cout << endl;
		}
		return;
	}

	void finalprice()
	{
		for (int i = 0; i < static_cast<int>(Tree_binomial[N].size()); i++)
		{
			Tree_binomial[N][i].second = max(0.0, Tree_binomial[N][i].first - strike);
		}
	}

	double pricing()
	{
		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = 0; j < static_cast<int>(Tree_binomial[i].size()); j++)
			{
				Tree_binomial[i][j].second = exp(-r*delta_t)*(pu*Tree_binomial[i + 1][j + 1].second + pd*Tree_binomial[i + 1][j].second);
			}
		}

		return Tree_binomial[0][0].second;
	}


	double pricing_pruning_setzero()
	{
		double s_up = spot*exp((r - sigma*sigma / 2)*T + 6 * sigma*sqrt(T));
		double s_low = spot*exp((r - sigma*sigma / 2)*T - 6 * sigma*sqrt(T));

		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = 0; j < static_cast<int>(Tree_binomial[i].size()); j++)
			{
				if (Tree_binomial[i + 1][j].first >= s_low&&Tree_binomial[i + 1][j + 1].first <= s_up) {
					Tree_binomial[i][j].second = exp(-r*delta_t)*(pu*Tree_binomial[i + 1][j + 1].second + pd*Tree_binomial[i + 1][j].second);
				}
				else {
					Tree_binomial[i][j].second = 0;
				}

			}
		}

		return Tree_binomial[0][0].second;

	}


	double pricing_pruning_intrinsicvalue()
	{
		double s_up = spot*exp((r - sigma*sigma / 2)*T + 6 * sigma*sqrt(T));
		double s_low = spot*exp((r - sigma*sigma / 2)*T - 6 * sigma*sqrt(T));

		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = 0; j < static_cast<int>(Tree_binomial[i].size()); j++)
			{
				if (Tree_binomial[i + 1][j].first >= s_low&&Tree_binomial[i + 1][j + 1].first <= s_up) {
					Tree_binomial[i][j].second = exp(-r*delta_t)*(pu*Tree_binomial[i + 1][j + 1].second + pd*Tree_binomial[i + 1][j].second);
				}
				else {
					Tree_binomial[i][j].second = max(spot - strike*exp(-r*delta_t*(N - i)), 0.0);
				}

			}
		}

		return Tree_binomial[0][0].second;

	}

	double pricing_pruning_linearapprox()
	{
		double s_up = spot*exp((r - sigma*sigma / 2)*T + 6 * sigma*sqrt(T));
		double s_low = spot*exp((r - sigma*sigma / 2)*T - 6 * sigma*sqrt(T));

		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = 0; j < static_cast<int>(Tree_binomial[i].size()); j++)
			{
				if (Tree_binomial[i + 1][j].first >= s_low&&Tree_binomial[i + 1][j + 1].first <= s_up) {
					Tree_binomial[i][j].second = exp(-r*delta_t)*(pu*Tree_binomial[i + 1][j + 1].second + pd*Tree_binomial[i + 1][j].second);
				}
				else {
					Tree_binomial[i][j].second = 0.5*Tree_binomial[i + 1][j + 1].second + 0.5*Tree_binomial[i + 1][j].second;
				}

			}
		}

		return Tree_binomial[0][0].second;

	}


	double pricing_RichardsonExtrapolation()
	{

		BinomialTree_TIAN TIAN1(spot, strike, sigma, r, T, N);
		TIAN1.build_BinomialTree();
		TIAN1.finalprice();


		BinomialTree_TIAN TIAN2(spot, strike, sigma, r, T, N / 2);
		TIAN2.build_BinomialTree();
		TIAN2.finalprice();

		double k = 1.0408;

		double p = (pow(2, k)*TIAN1.pricing() - TIAN2.pricing()) / (pow(2, k) - 1);

		return p;

	}




};