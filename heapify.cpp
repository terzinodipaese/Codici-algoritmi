#include <iostream>
#include <fstream>


using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");



template <typename T> class MaxHeap
{
private:
	int counter;
	int heapSize;
	T *arr;

	void swap(int i, int j)
	{
		T temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
	int parent(int i) { return i >> 1; }
	int left(int i) { return i << 1; }
	int right(int i) { return left(i) | 1; }
	
	void heapify(int i)
	{
		if(heapSize != 0)
			counter++;
		
		int l = left(i);
		int r = right(i);
		int max = i;
		
		if(((l <= heapSize) && (l >= 1)) && (arr[l] > arr[max]))
			max = l;
		
		if(((r <= heapSize) && (r >= 1)) && (arr[r] > arr[max]))
			max = r;
		
		if(max != i)
		{
			swap(i, max);
			heapify(max);
		}
	}
	
public:
	MaxHeap(int length, T *array)
	{
		counter = 0;
		heapSize = length;
		arr = new T[heapSize+1];
		
		for(int h=1; h<length+1; h++)
			arr[h] = array[h];
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
	
	void buildMaxHeap()
	{
		for(int i=heapSize/2; i>0; i--)
			heapify(i);
	}
	
	void printC()
	{
		out << counter << endl;
	}
};



int main()
{
	string tipo;
	int N;
	
	int *iarr;
	double *darr;
	bool *barr;
	char *carr;
	
	for(int i=0; i<100; i++)
	{
		in >> tipo >> N;
		
		if(tipo == "int")
		{
			iarr = new int[N+1];
			
			for(int j=1; j<N+1; j++)
				in >> iarr[j];
			
			MaxHeap<int> myHeap(N, iarr);
			myHeap.buildMaxHeap();
			for(int k=1; k<=N; k++)
				myHeap.extractMax();
			
			myHeap.printC();
		}
		
		if(tipo == "double")
		{
			darr = new double[N+1];
			
			for(int j=1; j<N+1; j++)
				in >> darr[j];
			
			MaxHeap<double> myHeap(N, darr);
			myHeap.buildMaxHeap();
			for(int k=1; k<=N; k++)
				myHeap.extractMax();
			
			myHeap.printC();
		}
		
		if(tipo == "bool")
		{
			barr = new bool[N+1];
			
			for(int j=1; j<N+1; j++)
				in >> barr[j];
			
			MaxHeap<bool> myHeap(N, barr);
			myHeap.buildMaxHeap();
			for(int k=1; k<=N; k++)
				myHeap.extractMax();
			
			myHeap.printC();
		}
		
		if(tipo == "char")
		{
			carr = new char[N+1];
			
			for(int j=1; j<N+1; j++)
				in >> carr[j];
			
			MaxHeap<char> myHeap(N, carr);
			myHeap.buildMaxHeap();
			for(int k=1; k<=N; k++)
				myHeap.extractMax();
			
			myHeap.printC();
		}
	}
	
	in.close();
	out.close();
	
	
	return 0;
}
















