#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


int findMax(int *arr, int len)
{
	int max = arr[0];
	
	for(int i=1; i<len; i++)
		if(arr[i] > max)
			max = arr[i];
	
	return max;
}

int findMin(int *arr, int len)
{
	int min = arr[0];
	
	for(int i=1; i<len; i++)
		if(arr[i] < min)
			min = arr[i];
		
	return min;
}



void countingSort(int *a, int n)
{
	int min = findMin(a, n);
	int max = findMax(a, n);
	int k = max - min + 1;
	
	int b[n];
	
	int c[k];		//tiene il numero di elementi con la stessa chiave
	
	for(int i=0; i<k; i++)
		c[i] = 0;
	
	for(int i=0; i<n; i++)
		c[a[i] - min]++;
		
	for(int i=1; i<k; i++)
		c[i] = c[i] + c[i-1];
	
	for(int i=n-1; i>=0; i--)
	{
		b[c[a[i] - min]-1] = a[i];
		c[a[i] - min]--;
	}
	
	for(int i=0; i<k; i++)
		out << c[i] << " ";
	
	for(int i=0; i<n; i++)
		out << b[i] << " ";
	
	out << endl;
}




int main()
{
	int N;
	
	for(int i=0; i<100; i++)			//ciclo sulle righe
	{
		in >> N;
		int vett[N];
		
		for(int j=0; j<N; j++)
			in >> vett[j];
		
		countingSort(vett, N);
	}
	
	return 0;
}

















