#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


template <typename T> class MaxHeap
{
private:
	int heapSize;
	T *arr;
	int parent(int i) { return i >> 1; }
	int left(int i) { return  i << 1; }
	int right(int i) { return left(i) | 1; }
	
	void swap(int i, int j)
	{
		T temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
	void heapify(int i)				//conserva la proprietà dell'heap, in questo caso del min-heap
	{
		int l = left(i);
		int r = right(i);
		int minimo = i;
		
		if(((l <= heapSize) && (l >= 1)) && (arr[l] < arr[minimo]))
			minimo = l;
		if(((r <= heapSize) && (r >= 1)) && (arr[r] < arr[minimo]))
			minimo = r;
		
		//dopo il secondo if, abbiamo trovato l'indice del massimo valore tra arr[i], arr[left(i)] e arr[right(i)]
		
		if(minimo != i)		//se minimo coincidesse con i, allora l'albero a cui stiamo applicando l'heapify sarebbe già un min-heap, quindi 
							//non dovremmo fare nulla
		{
			swap(minimo, i);
			heapify(minimo);
		}
	}
	
public:
	MaxHeap(int length, T *array)
	{
		heapSize = length;
		arr = new T[length+1];
		
		for(int j=1; j<heapSize+1; j++)
			arr[j] = array[j];
	}
	
	void buildMaxHeap()
	{
		for(int i = heapSize/2; i > 0; i--)
			heapify(i);
	}
	
	void printMaxHeap(ofstream &out)
	{
		for(int h=1; h<heapSize+1; h++)
			out << arr[h] << " ";
		
		out << endl;
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
			for(int f=1; f<N+1; f++)
				in >> iarr[f];
			
			MaxHeap<int> myHeap(N, iarr);
			
			myHeap.buildMaxHeap();
			
			myHeap.printMaxHeap(out);
		}
		
		if(tipo == "double")
		{
			darr = new double[N+1];
			for(int f=1; f<N+1; f++)
				in >> darr[f];
			
			MaxHeap<double> myHeap(N, darr);
			
			myHeap.buildMaxHeap();
			
			myHeap.printMaxHeap(out);
		}
		
		if(tipo == "bool")
		{
			barr = new bool[N+1];
			for(int f=1; f<N+1; f++)
				in >> barr[f];
			
			MaxHeap<bool> myHeap(N, barr);
			
			myHeap.buildMaxHeap();
			
			myHeap.printMaxHeap(out);
		}
		
		if(tipo == "char")
		{
			carr = new char[N+1];
			for(int f=1; f<N+1; f++)
				in >> carr[f];
			
			MaxHeap<char> myHeap(N, carr);
			
			myHeap.buildMaxHeap();
			
			myHeap.printMaxHeap(out);
		}
		
	}
	
	in.close();
	out.close();
	
	return 0;
}

