#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int max(int x, int y)
{
	if(x >= y) return x;
	
	return y;
}

int zaino(int W, int wt[], int val[], int n)
{
	int K[n+1][W+1];
	
	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=W; j++)
		{	
			//se il numero di oggetti o il peso massimo dello zaino è 0, allora si ha valore 0
			if(i==0 || j==0)
				K[i][j] = 0;
			//se il peso dell'i-esimo oggetto è più piccolo o uguale al peso dello zaino
			else if(wt[i-1] <= j)
				K[i][j] = max(val[i-1] + K[i-1][j-wt[i-1]], K[i-1][j]);
			//altrimenti l'oggetto non può essere incluso nella soluzione
			else
				K[i][j]= K[i-1][j];
		}
	}
	
	return K[n][W];
}





int main()
{
	int noggetti, pesozaino;
	
	for(int i=0; i<100; i++)
	{
		in >> noggetti >> pesozaino;
		int wt[noggetti];		//tutti gli oggetti hanno peso unitario
		int val[noggetti];		//array dei valori degli noggetti
		
		for(int i=0; i<noggetti; i++)
		{
			wt[i] = 1;
			in >> val[i];
		}
		
		out << zaino(pesozaino, wt, val, noggetti) << endl;
	}
	
	in.close();
	out.close();
	
	return 0;
}




















