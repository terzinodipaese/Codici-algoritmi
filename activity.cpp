#include <iostream>
#include <fstream>
//ricorda che della matrice non devi tornare quello nell'ultima posizione, 
//ma il massimo della riga.

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

class Attivita
{
private:
	int I, F;

public:
	Attivita(int i, int f)
	{
		I = i;
		F = f;
	}
	
	int getInizio(){ return I; }
	int getFine(){ return F; }

	bool operator>(Attivita* Obj)
	{
		if(this->F > Obj->F)
			return true;
		if(this->F < Obj->F)
			return false;
		return this->I > Obj->I;
	}
};


void InsertionSort(Attivita** A,int N)
{
	for(int i = 1; i < N; ++i)
	{
		int j = i;
		Attivita* a = A[j];
		while(j > 0 && *A[j-1] > a)
		{
			A[j] = A[j-1];
			j--;
		}

		A[j] = a;
	}
}

int MaxActivity(Attivita** A, int c)
{
	int r = A[c-1]->getFine() + 1;
	int M[r][c];

	for(int i = 0; i < r; ++i)
	{
		for(int j = 0; j < c; ++j)
		{
			if(i < A[j]->getFine())
				M[i][j] = 0;
			else
			{
				int max = 0;
				for(int k = 0; k < j; ++k)
					if(max < M[A[j]->getInizio()][k])
						max = M[A[j]->getInizio()][k];

				M[i][j] = max + A[j]->getFine() - A[j]->getInizio();
			}
		}
	}


	int max = 0;
	for (int k = 0; k < c; ++k)
		if(max < M[r-1][k]) 
			max = M[r-1][k];

	return max;
}

int main()
{
	int N;
	Attivita **A;
	for(int count = 0; count < 100; ++count)
	{
		fin >> N;
		A = new Attivita*[N];

		int I, F;
		char c;
		for(int i=0; i<N; i++)
		{
			fin >> c >> I >> F >> c;
			A[i] = new Attivita(I, F);
		}
		

		InsertionSort(A, N);


		fout << MaxActivity(A, N) << endl;		
	}
	
	fin.close();
	fout.close();

	return 0;
}
