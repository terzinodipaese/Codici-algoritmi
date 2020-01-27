#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


int minimo(int x, int y)
{
	if(x < y) return x;
	return y;
}

long long int resto(int *coins, int R, int n_coins)
{
	int x, y;

	long long int tab[R+1][n_coins+1];	//creiamo la tabella dei risultati temporanei

	//nel caso in cui il resto da restituire sia 0,
	//il numero di monete da dare è chiaramente 0
	for(int i=0; i<=n_coins; i++)	
		tab[0][i] = 0;

	//se abbiamo 0 monete, quale che sia il resto da dare,
	//escluso il caso resto = 0,
	//esso non potrà essere dato
	for(int i=1; i<=R; i++)
		tab[i][0] = INT_MAX/2;

	for(int i=1; i<=R; i++)
	{
		for(int j=1; j<=n_coins; j++)
		{
			//se la (j-1)-esima moneta è più piccola del
			//resto da dare
			if(coins[j-1] <= i)
			{
				//numero di monete per dare resto i
				//senza utilizzare la j-esima moneta
				x = tab[i][j-1];

				//numero di monete per dare resto
				//i meno coins[j-1](la j-1 esima moneta)
				//con j monete + 1
				y = 1 + tab[i-coins[j-1]][j];

				tab[i][j] = minimo(x, y);
			}

			else
				//in questo caso escludiamo la 
				tab[i][j] = tab[i][j-1];
		}
	}

	return tab[R][n_coins];
}

void selectionsort(int *a, int len)
{
	int min;
	for(int i=0; i<len; i++)
	{
		min = i;
		for(int j=i+1; j<len; j++)
		{
			if(a[j] < a[min])
				min = j;
		}

		int temp = a[min];
		a[min] = a[i];
		a[i] = temp;
	}
}


int main()
{
	int R, ncoins, *coins;

	for(int i=0; i<100; i++)		//ciclo sulle righe
	{
		in >> R >> ncoins;
		coins = new int[ncoins];

		//ciclo sugli inserimenti delle monete
		for(int j=0; j<ncoins; j++)
			in >> coins[j];

		selectionsort(coins, ncoins);

		out << resto(coins, R, ncoins) << endl;

		delete[] coins;		//dealloca l'array
	}

	in.close();
	out.close();

	return 0;
}