#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int chiamate;

template <typename T> class Terna
{
private:
	T x, y, z;

public:
	Terna(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	bool operator>(Terna<T> obj)
	{
		if((this->x > obj.x))
			return true;
		if((this->x == obj.x) && (this->y > obj.y))
			return true;
		if((this->x == obj.x) && (this->y == obj.y) && (this->z > obj.z))
			return true;
		else
			return false;
	}
	
	void print()
	{
		out << "(" << x << "," << y << "," << z << ") ";
	}
};

int left(int i) { return i << 1; }
int right(int i) { return left(i) | 1; }
int parent(int i) { return i >> 1; }

//prende l'array delle coppie, l'indice su cui applicare heapify e nElem
template <typename T> void heapify(Terna<T> *terne[], int i, int nElem)
{
	if(nElem != 0)
		chiamate++;
	int sinistro = left(i);
	int destro = right(i);
	int max = i;
	
	if(sinistro <= nElem && *terne[sinistro] > *terne[max])
		max = sinistro;
	if(destro <= nElem && *terne[destro] > *terne[max])
		max = destro;
	
	if(max != i)
	{
		terne[0] = terne[max];
		terne[max] = terne[i];
		terne[i] = terne[0];
		heapify(terne, max, nElem);
	}
}

template <typename T> void extractMax(Terna<T> *terne[], int& nElem)
{
	terne[0] = terne[1];
	terne[1] = terne[nElem];
	terne[nElem] = terne[0];
	nElem--;
	heapify(terne, 1, nElem);
}


template <typename T> void buildHeap(Terna<T> *terne[], int nElem)
{
	for(int i=nElem/2; i>=1; i--)
		heapify(terne, i, nElem);
}








int main()
{
	string tipo;
	int numTerne;
	char c;
	
	for(int i=0; i<100; i++)
	{
		in >> tipo >> numTerne;
		
		if(tipo == "int")
		{
			chiamate = 0;
			int a, b, d;
			Terna<int> *terne[numTerne+1];
			
			for(int j=1; j<=numTerne; j++)
			{
				in >> c >> a >> b >> d >> c;
				terne[j] = new Terna<int>(a, b, d);
			}
			
			buildHeap(terne, numTerne);
			int n = numTerne;
			for(int j=1; j<=numTerne; j++)
				extractMax(terne, n);
			
			out << chiamate << " ";
			for(int j=1; j<=numTerne; j++)
				terne[j]->print();
			out << endl;
			
			for(int j=1; j<=numTerne; j++)
				delete terne[j];
		}
		
		
		if(tipo == "double")
		{
			chiamate = 0;
			double a, b, d;
			Terna<double> *terne[numTerne+1];
			
			for(int j=1; j<=numTerne; j++)
			{
				in >> c >> a >> b >> d >> c;
				terne[j] = new Terna<double>(a, b, d);
			}
			
			buildHeap(terne, numTerne);
			int n = numTerne;
			for(int j=1; j<=numTerne; j++)
				extractMax(terne, n);
			
			out << chiamate << " ";
			for(int j=1; j<=numTerne; j++)
				terne[j]->print();
			out << endl;
			
			for(int j=1; j<=numTerne; j++)
				delete terne[j];
		}
		
		
		if(tipo == "bool")
		{
			chiamate = 0;
			bool a, b, d;
			Terna<bool> *terne[numTerne+1];
			
			for(int j=1; j<=numTerne; j++)
			{
				in >> c >> a >> b >> d >> c;
				terne[j] = new Terna<bool>(a, b, d);
			}
			
			buildHeap(terne, numTerne);
			int n = numTerne;
			for(int j=1; j<=numTerne; j++)
				extractMax(terne, n);
			
			out << chiamate << " ";
			for(int j=1; j<=numTerne; j++)
				terne[j]->print();
			out << endl;
			
			for(int j=1; j<=numTerne; j++)
				delete terne[j];
		}
		
		
		if(tipo == "char")
		{
			chiamate = 0;
			char a, b, d;
			Terna<char> *terne[numTerne+1];
			
			for(int j=1; j<=numTerne; j++)
			{
				in >> c >> a >> b >> d >> c;
				terne[j] = new Terna<char>(a, b, d);
			}
			
			buildHeap(terne, numTerne);
			int n = numTerne;
			for(int j=1; j<=numTerne; j++)
				extractMax(terne, n);
			
			out << chiamate << " ";
			for(int j=1; j<=numTerne; j++)
				terne[j]->print();
			out << endl;
			
			for(int j=1; j<=numTerne; j++)
				delete terne[j];
		}
	}
	
	in.close();
	out.close();
	
	return 0;
}












