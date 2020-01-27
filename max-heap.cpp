#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


template <typename T> class PQueue
{
private:
	T *arr;
	int heapSize;
	int arrayLen;
	
	int left(int i) { return i << 1; }
	int right(int i) { return left(i) | 1; }
	int parent(int i) { return i >> 1; }
	
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
		
		int massimo = i;
		
		if(((l <= heapSize) && (l >= 1)) && (arr[l] > arr[massimo]))
			massimo = l;
		if(((r <= heapSize) && (r >= 1)) && (arr[r] > arr[massimo]))
			massimo = r;
		
		if(massimo != i)
		{
			swap(massimo, i);
			heapify(massimo);
		}
	}
	
public:
	
	int counter;			//tiene il conteggio delle chiamate di heapify
	
	PQueue(int arraySize)
	{
		heapSize = 0;
		arrayLen = arraySize+1;
		arr = new T[arrayLen];
		counter = 0;
	}
	
	void insertKey(T key)
	{
		heapSize++;
		arr[heapSize] = key;
		
		int i = heapSize;
		while((i > 1) && (arr[i] > arr[parent(i)]))
		{
			swap(i, parent(i));
			i = parent(i);
		}
	}
	
	
	//in teoria dovrebbe ritornare il max, ma per quello che bisogna fare non serve
	void extractMax()
	{
		if(heapSize < 1)			//coda con priorità vuota
			return;
		
		else
		{
			swap(1, heapSize);
			heapSize--;
			heapify(1);
		}
	}
	
	
	void printPQueue(ofstream &out)
	{
		out << counter << " ";
		for(int i=1; i<=heapSize; i++)
			out << arr[i] << " ";
		out << endl;
	}
	
};

int main()
{
	string tipo, operazione;
	int Nop;
	
	int auxi;
	double auxd;
	bool auxb;
	char auxc;
	
	
	for(int i=0; i<100; i++)					//ciclo sulle righe
	{
		in >> tipo >> Nop;
		
		if(tipo == "int")
		{
			PQueue<int> myQ(Nop);
			
			for(int h=0; h<Nop; h++)		//ciclo sulle operazioni
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
			
			myQ.printPQueue(out);
		}
		
		
		
		if(tipo == "double")
		{
			PQueue<double> myQ(Nop);
			
			for(int h=0; h<Nop; h++)		//ciclo sulle operazioni
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
			
			myQ.printPQueue(out);
		}
		
		
		if(tipo == "bool")
		{
			PQueue<bool> myQ(Nop);
			
			for(int h=0; h<Nop; h++)		//ciclo sulle operazioni
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

			myQ.printPQueue(out);
		}
		
		if(tipo == "char")
		{
			PQueue<char> myQ(Nop);
			
			for(int h=0; h<Nop; h++)		//ciclo sulle operazioni
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
			
			myQ.printPQueue(out);
		}
	}
	
	
	in.close();
	out.close();
	
	
	return 0;
}

















