#include <iostream>
#include <fstream>
#include <typeinfo>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <typename T> T findMax(T *arr, int len)
{
	T max = arr[0];
	
	for(int i=0; i<len; i++)
		if(arr[i] > max)
			max = arr[i];
		
	return max;
}

template <typename T> T findMin(T *arr, int len)
{
	T min = arr[0];
	
	for(int i=0; i<len; i++)
		if(arr[i] < min)
			min = arr[i];
		
	return min;
}


template <typename T> void countingSort(T *a, int len)
{
	int min = findMin(a, len);
	int max = findMax(a, len);
	int k = max - min + 1;
	
	T b[len];
	int c[k];
	
	for(int i=0; i<k; i++)
		c[i] = 0;
	
	for(int i=0; i<len; i++)
		c[a[i] - min]++;
	
	for(int i=1; i<k; i++)
		c[i] = c[i] + c[i-1];
	
	for(int i=len-1; i>=0; i--)
	{
		b[c[a[i] - min]-1] = a[i];
		c[a[i] - min]--;
	}
	
	for(int i=0; i<k; i++)
		out << c[i] << " ";
	
	
	for(int i=0; i<len; i++)
		out << b[i] << " ";
	
	out << endl;
}



void countingSort(double *a, int len)		//versione per double
{
	int appoggio[len];
	for(int i=0; i<len; i++)
		appoggio[i] = a[i] * 10;
	
	
	int min = findMin(appoggio, len);
	int max = findMax(appoggio, len);
	int k = max - min + 1;
	
	int b[len];
	int c[k];
	
	for(int i=0; i<k; i++)
		c[i] = 0;
	
	for(int i=0; i<len; i++)
		c[appoggio[i] - min]++;
	
	for(int i=1; i<k; i++)
		c[i] = c[i] + c[i-1];
	
	for(int i=len-1; i>=0; i--)
	{
		b[c[appoggio[i] - min]-1] = appoggio[i];
		c[appoggio[i] - min]--;
	}
	
	for(int i=0; i<k; i++)
		out << c[i] << " ";
	
	
	for(int i=0; i<len; i++)
		out << (double)b[i]/10 << " ";
	
	out << endl;
}


int main()
{
	string tipo;
	int N;
	
	int *arri;
	bool *arrb;
	char *arrc;
	double *arrd;
	
	for(int i=0; i<100; i++)
	{
		in >> tipo >> N;
		
		if(tipo == "int")
		{
			arri = new int[N];
			for(int j=0; j<N; j++)
				in >> arri[j];
			
			countingSort(arri, N);
		}
		
		if(tipo == "double")
		{
			arrd = new double[N];
			for(int j=0; j<N; j++)
				in >> arrd[j];
			
			countingSort(arrd, N);
		}
		
		if(tipo == "bool")
		{
			arrb = new bool[N];
			for(int j=0; j<N; j++)
				in >> arrb[j];
			
			countingSort(arrb, N);
		}
		
		if(tipo == "char")
		{
			arrc = new char[N];
			for(int j=0; j<N; j++)
				in >> arrc[j];
			
			countingSort(arrc, N);
		}
	}
	
	in.close();
	out.close();
	
	return 0;
}











