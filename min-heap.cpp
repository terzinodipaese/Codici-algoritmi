#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>


using namespace std;


ifstream in("input.txt");
ofstream out("output.txt");


template <typename T> class PQueue
{
private:
	int counter;		//tiene traccia delle chiamate a heapify
	int heapSize;		//numero di elementi veramente presenti nell'array
	T *arr;			
	int arrayLen;		//dimensione del vettore
	
	int parent(int i) { return i >> 1; }
	int left(int i) { return i << 1; }
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
		int min = i;
		
		if(((l <= heapSize) && (l >= 1)) && (arr[l] < arr[min]))
			min = l;
		
		if(((r <= heapSize) && (r>= 1)) && (arr[r] < arr[min]))
			min = r;
		
		if(min != i)
		{
			swap(min, i);
			heapify(min);
		}
	}
	
public:
	PQueue(int arraySize)
	{
		heapSize = 0;
		arrayLen = arraySize + 1;
		arr = new T[arrayLen];
		counter = 0;
	}
	
	void insertKey(T key)
	{
		heapSize++;
		arr[heapSize] = key;
		
		int i = heapSize;
		while((i > 1) && (arr[i] < arr[parent(i)]))
		{
			swap(i, parent(i));
			i = parent(i);
		}
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
	
	void printPQueue()
	{
		out << counter << " ";
		for(int i=1; i<=heapSize; i++)
			out << arr[i] << " ";
		
		out << endl;
	}
};



int main()
{
	int numop;
	string operazione, tipo;
	int auxi;
	double auxd;
	bool auxb;
	char auxc;
	
	
	for(int i=0; i<100; i++)
	{
		in >> tipo >> numop;
		
		if(tipo == "int")
		{
			PQueue<int> myQ(numop);
			
			for(int h=0; h<numop; h++)		//ciclo sulle operazioni
			{
				in >> operazione;
				
				if(operazione == "extract")
					myQ.extractMax();
				
				else
				{
					operazione = operazione.substr(2);
					auxi = atoi(operazione.c_str());
					myQ.insertKey(auxi);
				}
			}
			
			myQ.printPQueue();
		}
		
		
		
		if(tipo == "double")
		{
			PQueue<double> myQ(numop);
			
			for(int h=0; h<numop; h++)		//ciclo sulle operazioni
			{
				in >> operazione;
				
				if(operazione == "extract")
					myQ.extractMax();
				
				else
				{
					operazione = operazione.substr(2);
					auxd = atof(operazione.c_str());
					myQ.insertKey(auxd);
				}
			}
			
			myQ.printPQueue();
		}
		
		if(tipo == "bool")
		{
			PQueue<bool> myQ(numop);
			
			for(int h=0; h<numop; h++)		//ciclo sulle operazioni
			{
				in >> operazione;
				
				if(operazione == "extract")
					myQ.extractMax();
				
				else
				{
					operazione = operazione.substr(2);
					auxb = atoi(operazione.c_str());
					myQ.insertKey(auxb);
				}
			}
			
			myQ.printPQueue();
		}
		
		if(tipo == "char")
		{
			PQueue<char> myQ(numop);
			
			for(int h=0; h<numop; h++)		//ciclo sulle operazioni
			{
				in >> operazione;
				
				if(operazione == "extract")
					myQ.extractMax();
				
				else
				{
					auxc = operazione[2];
					myQ.insertKey(auxc);
				}
			}
			
			myQ.printPQueue();
		}
	}
	
	in.close();
	out.close();
	
	return 0;
}










