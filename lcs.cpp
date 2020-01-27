#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int max(int num1, int num2)
{
	if(num1 < num2)
		return num2;
	else
		return num1;
}

int lcs(char *x, char *y, int lenX, int lenY)
{
	int L[lenX+1][lenY+1];
	
	for(int i=0; i<=lenX; i++)
	{
		for(int j=0; j<=lenY; j++)
		{
			if(i == 0 || j == 0)
				L[i][j] = 0;
			
			else if(x[i-1] == y[j-1])
				L[i][j] = L[i-1][j-1] + 1;
			
			else
				L[i][j] = max(L[i-1][j], L[i][j-1]);
		}
	}
	
	return L[lenX][lenY];
}

int main()
{
	int N, M;
	
	for(int i=0; i<100; i++)
	{
		in >> M >> N;
		char sequenza1[M], sequenza2[N];
		in >> sequenza1 >> sequenza2;
		
		out << lcs(sequenza1, sequenza2, M, N) << endl;
	}
	
	in.close();
	out.close();
	
	return 0;
}





