#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


//p è l'array delle dimensioni delle matrici, n è il numero di matrici
int matrixChainOrder(int *p, int n)
{
	int m[n+1][n+1];		//tabella che contiene il numero delle moltiplicazioni
	
	//L è la lunghezza della sequenza di matrici
	//j è l'indice dell'ultima matrice
	//q tiene il numero di moltiplicazioni per un dato indice k
	int L, j, q, i;			
	
	for(i=1; i<=n; i++)
		m[i][i] = 0;
	
	//L parte da 2 perchè abbiamo già calcolato i costi per le sequenze da una sola 
	//matrice, che sono tutti uguali a zero(in una sequenza di 1 matrice non dobbiamo
	//fare moltiplicazioni), per costo si intende il numero di moltiplicazioni
	for(L=2; L<=n; L++)
	{
		for(i=1; i<=n-L+1; i++)
		{
			j = i+L-1;
			m[i][j] = INT_MAX;	//INT_MAX simula +infinito, cioè il peggior minimo
			
			//al variare di k, cioè delle parentesizzazioni
			for(int k=i; k<=j-1; k++)
			{
				q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if(q < m[i][j])
					m[i][j] = q;
			}
		}
	}
	
	return m[1][n];
}




int main()
{
	int N;
	char c;
	int *pProv;
	int *pFin;
	
	
	for(int i=0; i<100; i++)		//ciclo sulle righe
	{
		in >> N;					//numero di matrici
		pProv = new int[2*N];		//array provvisorio delle dimensioni
		pFin = new int[N+1];		//array finale delle dimensioni, cioè quello che utilizzerò
		
		
		//indice di pProv
		int index = 0;
		for(int j=0; j<N; j++)
		{
			in >> c >> pProv[index];
			index++;
			in >> c >> pProv[index] >> c;
			index++;
		}
		
		
		
		//questa parte serve a togliere i doppioni
		//indice di pFin
		int index2 = 0;
		pFin[index2] = pProv[0];
		index2++;
		for(int h=1; h<=(2*N)-3; h+=2)
		{
			pFin[index2] = pProv[h];
			index2++;
		}
		pFin[index2] = pProv[(2*N)-1];
		
		out << matrixChainOrder(pFin, N) << endl;
	}
	
	int num = 4;
	int vect[] = {1, 2, 3, 4};
	cout << matrixChainOrder(vect, num) << endl;
	
	
	in.close();
	out.close();
	
	
	return 0;
}






