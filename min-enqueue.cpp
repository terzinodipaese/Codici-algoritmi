/*
	Coda con priorità implementata con un min-heap
*/

#include <iostream>
#include <fstream>

using namespace std;


ifstream in("input.txt");
ofstream out("output.txt");


template <typename P> class PQueue
{
private:
	P *arr;
	int arrayLen;
	int heapSize;			//tiene il numero di elementi nella coda con priorità, inizialmente è posto a zero
	int left(int i) { return i << 1; }
	int right(int i) { return left(i) | 1; }
	int parent(int i) { return i >> 1; }
	
	void swap(int i, int j)
	{
		P temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
public:
	PQueue(int arraySize)
	{
		heapSize = 0;
		arrayLen = arraySize+1;			//tiene traccia della dimensione fisica dell'array, DIVERSO da heapSize!!!!!
		arr = new P[arraySize+1];		//questo perchè gli indici partono da 1, allora abbiamo bisogno di allocare una "cella" in più
	}
	
	void insertKey(P key)				//inseriamo le chiavi a partire da arr[1], sprechiamo una cella di memoria quindi, ma non possiamo fare altrimenti
	{
		heapSize++;
		arr[heapSize] = key;
		
		int i = heapSize;
		
		//sostanzialmente questo ciclo fa risalire la nuova chiave inserita alla sua posizione naturale, secondo la proprietà del min-heap
		while((i > 1) && (arr[i] < arr[parent(i)]))			//arr[i] < arr[parent(i)] perchè stiamo implementando un min-heap
		{
			swap(i, parent(i));
			i = parent(i);
		}
	}
	
	void printPQueue(ofstream &out)
	{
		for(int j=1; j<arrayLen; j++)
			out << arr[j] << " ";
		out << endl;
	}
};




int main()
{
	string tipo;
	int N;
	int auxi;
	double auxd;
	bool auxb;
	char auxc;
	
	
	for(int i=0; i<100; i++)
	{
		in >> tipo >> N;
		
		if(tipo == "int")
		{
			PQueue<int> myQ(N);
			for(int t=0; t<N; t++)
			{
				in >> auxi;
				myQ.insertKey(auxi);
			}
			
			myQ.printPQueue(out);
		}
		
		if(tipo == "double")
		{
			PQueue<double> myQ(N);
			for(int t=0; t<N; t++)
			{
				in >> auxd;
				myQ.insertKey(auxd);
			}
			
			myQ.printPQueue(out);
		}
		
		if(tipo == "bool")
		{
			PQueue<bool> myQ(N);
			for(int t=0; t<N; t++)
			{
				in >> auxb;
				myQ.insertKey(auxb);
			}
			
			myQ.printPQueue(out);
		}
		
		if(tipo == "char")
		{
			PQueue<char> myQ(N);
			for(int t=0; t<N; t++)
			{
				in >> auxc;
				myQ.insertKey(auxc);
			}
			
			myQ.printPQueue(out);
		}
	}
	
	in.close();
	out.close();
	
	return 0;
}















