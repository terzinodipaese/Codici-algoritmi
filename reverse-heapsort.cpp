#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <typename T> class MinHeap
{
private:
	T *arr;
	int heapSize;			//tiene il numero di elementi dell'heap, PUO CAMBIARE!!!!
	int arrayLen;			//il suo valore non cambia per tutto il programma!!!!
	int counter;

	int left(int i) { return i << 1; }
	int parent(int i) { return i >> 1; }
	int right(int i) { return left(i) | 1; }
	
	void swap(int i, int j)
	{
		T temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
	void heapify(int i)
	{
		if(heapSize != 0)
			counter++;
		
		int l = left(i);
		int r = right(i);
		int max = i;
		
		if(((l <= heapSize) && (l >= 1)) && (arr[l] < arr[max]))
			max = l;
		
		if(((r <= heapSize) && (r >= 1)) && (arr[r] < arr[max]))
			max = r;
		
		if(max != i)
		{
			swap(i, max);
			heapify(max);
		}
	}
	
public:
	MinHeap(int len, T *array)
	{
		counter = 0;
		heapSize = len;
		arrayLen = len;			//servirà per stampare l'array alla fine
		arr = new T[len + 1];
		
		for(int h = 1; h < len +1; h++)
			arr[h] = array[h];
	}
	
	void buildMinHeap()
	{
		for(int i = heapSize/2; i > 0; i--)
			heapify(i);
	}
	
	void extractMax()
	{
		if(heapSize < 1)
			return;
		
		else
		{
			swap(1, heapSize);
			heapSize--;
			heapify(1);
		}
	}
	
	void heapSort()
	{
		buildMinHeap();
		for(int i=1; i<=arrayLen; i++)			//IMPORTANTE: non mettere heapSize, ma arrayLen!!!!!!!!!
			extractMax();
	}
	
	void print()
	{
		out << counter << " ";
		for(int i = 1; i <= arrayLen; i++)
			out << arr[i] << " ";
		
		out << endl;
	}
	
};


int main()
{
	string tipo;
	int N;
	int *arri;
	double *arrd;
	bool *arrb;
	char *arrc;
	
	for(int i=0; i<100; i++)
	{
		in >> tipo >> N;
		
		if(tipo == "int")
		{
			arri = new int[N+1];
			
			for(int j=1; j <= N; j++)
				in >> arri[j];
			
			MinHeap<int> myHeap(N, arri);
			myHeap.heapSort();
			
			myHeap.print();
		}
		
		if(tipo == "double")
		{
			arrd = new double[N+1];
			
			for(int j=1; j <= N; j++)
				in >> arrd[j];
			
			MinHeap<double> myHeap(N, arrd);
			myHeap.heapSort();
			
			myHeap.print();
		}
		
		if(tipo == "bool")
		{
			arrb = new bool[N+1];
			
			for(int j=1; j <= N; j++)
				in >> arrb[j];
			
			MinHeap<bool> myHeap(N, arrb);
			myHeap.heapSort();
			
			myHeap.print();
		}
		
		if(tipo == "char")
		{
			arrc = new char[N+1];
			
			for(int j=1; j <= N; j++)
				in >> arrc[j];
			
			MinHeap<char> myHeap(N, arrc);
			myHeap.heapSort();
			
			myHeap.print();
		}
	}
	
	
	in.close();
	out.close();
	
	return 0;
}