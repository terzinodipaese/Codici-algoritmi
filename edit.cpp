#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int min(int a, int b, int c)
{
	if((a<=b) && (a<=c))
		return a;
	if((b<=a) && (b<=c))
		return b;
	else
		return c;
}

int edit(string str1, string str2, int m, int n)
{
	//tabella che memorizza i risultatti intermedi
	int tabella[m+1][n+1];
	
	for(int i=0; i<=m; i++)
	{
		for(int j=0; j<=n; j++)
		{
			//se la lunghezza della prima stringa è zero
			if(i == 0)
				tabella[i][j] = j;
			//se la lunghezza della seconda stringa è zero
			else if(j == 0)
				tabella[i][j] = i;
			//se gli ultimi caratteri sono uguali
			else if(str1[i-1] == str2[j-1])
				tabella[i][j] = tabella[i-1][j-1];
			else
				tabella[i][j] = 1 + min(tabella[i][j-1], 
									tabella[i-1][j],
									tabella[i-1][j-1]);
		}
	}
	
	return tabella[m][n];
}



int main()
{
	string str1, str2;
	int lstr1, lstr2;
	
	for(int i=0; i<100; i++)
	{
		in >> lstr1 >> lstr2 >> str1 >> str2;
		out << edit(str1, str2, lstr1, lstr2) << endl;
	}
	
	in.close();
	out.close();
	
	return 0;
}








