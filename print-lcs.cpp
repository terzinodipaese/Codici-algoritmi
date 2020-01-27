#include <iostream>
#include <fstream>

#define SOPRA 0
#define DIAGONALE 1
#define SINISTRA 2

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

//RICORDA: quando bisogna ritornare un 
//array, allocalo dinamicamente

int** lcs(char *x, char *y, int lenx, int leny)
{
	int L[leny+1][lenx+1];
	
	int **F = new int*[leny+1];
	for(int i=0; i<leny+1; i++)
		F[i] = new int[lenx+1];
	
	
	for(int j=0; j<=leny; j++)		//righe
	{
		for(int i=0; i<=lenx; i++)	//colonne
		{
			if(i==0 || j==0)
				L[j][i] = 0;
			
			else if(x[i-1] == y[j-1])
			{
				L[j][i] = L[j-1][i-1] + 1;
				F[j][i] = DIAGONALE;
			}
			
			else if(L[j-1][i] >= L[j][i-1])
			{
				L[j][i] = L[j-1][i];
				F[j][i] = SOPRA;
			}
			
			else
			{
				L[j][i] = L[j][i-1];
				F[j][i] = SINISTRA;
			}
		}
	}
	
	return F;
}

void printlcs(int **F, char *y, int j, int i)
{
	if(i==0 || j==0)
		return;
	
	if(F[j][i] == DIAGONALE)
	{
		printlcs(F, y, j-1, i-1);
		out << y[j-1];
	}
	
	else if(F[j][i] == SOPRA)
		printlcs(F, y, j-1, i);
	else
		printlcs(F, y, j, i-1);
}




int main()
{
	int N, M;
	for(int i=0; i<100; i++)
	{
		in >> M >> N;
		char sequenza1[M], sequenza2[N];
		in >> sequenza1 >> sequenza2;
		printlcs(lcs(sequenza1, sequenza2, M, N), sequenza2, N, M);
		out << endl;
	}
	
	return 0;
}











