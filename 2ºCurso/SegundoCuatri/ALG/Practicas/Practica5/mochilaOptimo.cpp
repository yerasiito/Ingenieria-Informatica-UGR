// C++ program to find maximum achievable value
// with a knapsack of weight W and multiple
// instances allowed.
#include<bits/stdc++.h>
using namespace std;

// Returns the maximum value with knapsack of
// W capacity
int unboundedKnapsack(int peso_max, int nitems, int beneficio[], int pesos[])
{
	// dp[i] is going to store maximum value
	// with knapsack capacity i.
	int dp[peso_max+1];
	memset(dp, 0, sizeof dp);

	// Fill dp[] using above recursive formula
	for (int i=0; i<=peso_max; i++)
	for (int j=0; j<nitems; j++)
		if (pesos[j] <= i)
			dp[i] = max(dp[i], dp[i-pesos[j]] + beneficio[j]);
	
	return dp[peso_max];
}

// Driver program
int main()
{
	const int MAX_PESO = 1000000;
	int beneficio[] = {10,7,9,5,7,1,10,6,8,2,8,8,3,9,4};
	int peso[] = {3,6,4,3,3,5,4,5,3,6,4,3,6,6,4};
	int n = sizeof(beneficio)/sizeof(beneficio[0]);

	cout << "\nBeneficio " << unboundedKnapsack(MAX_PESO, n, beneficio, peso);

	return 0;
}
