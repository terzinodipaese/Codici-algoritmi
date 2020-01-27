#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int chiamate;

template <typename C> class Coppia
{
private:
	C x, y;

public:
	Coppia(C x, C y)
	{
		this->x = x;
		this->y = y;
	}
	
	//una coppia è maggiore dell'altra se x1 > x2, oppure
	//se x1 == x2 E y1 > y2
	bool operator>(Coppia<C> obj)
	{
		if(this->x > obj.x)
			return true;
		else if((this->x == obj.x) && (this->y > obj.y))
			return true;
		else
			return false;
	}
	
	//le due coppie sono uguali se i loro elementi sono
	//uguali membro a membro
	bool operator==(Coppia<C> obj)
	{
		if((this->x == obj.x) && (this->y == obj.y))
			return true;
		return false;
	}
	
	void print()
	{
		out << "(" << x << "," << y << ") ";
	}
};

int left(int i) { return i << 1;}
int right(int i) { return left(i) | 1; }
int parent(int i) { return i >> 1; }

//prende in come parametri un array di coppie e l'indice
template <typename C> void heapify(Coppia<C> *coppie[], int i, int nElem)
{
	if(nElem != 0)
		chiamate++;
	int max = i;
	int sinistro = left(i);
	int destro = right(i);
	
	if(sinistro <= nElem && *coppie[sinistro] > *coppie[max])
		max = sinistro;
	if(destro <= nElem && *coppie[destro] > *coppie[max])
		max = destro;
	
	if(max != i)
	{
		coppie[0] = coppie[max];
		coppie[max] = coppie[i];
		coppie[i] = coppie[0];
		heapify(coppie, max, nElem);
	}
}

template <typename C> void extractMax(Coppia<C> *coppie[], int& nElem)
{
	coppie[0] = coppie[1];
	coppie[1] = coppie[nElem];
	coppie[nElem] = coppie[0];
	nElem--;
	heapify(coppie, 1, nElem);
}

template <typename C> void buildHeap(Coppia<C> *coppie[], int nElem)
{
	for(int i=nElem/2; i>=1; i--)
		heapify(coppie, i, nElem);
}


int main()
{
	string tipo;
	int numCoppie;
	char c;
	
	for(int i=0; i<100; i++)		//ciclo sulle righe
	{
		in >> tipo >> numCoppie;
	
		if(tipo == "int")
		{
			chiamate = 0;
			int a, b;
			Coppia<int> *coppie[numCoppie+1];
			for(int j=1; j<=numCoppie; j++)
			{
				in >> c >> a >> b >> c;
				coppie[j] = new Coppia<int>(a, b);
			}
			
			buildHeap(coppie, numCoppie);
			int n = numCoppie;
			for(int j=1; j<=numCoppie; j++)
				extractMax(coppie, n);
			
			out << chiamate << " ";
			for(int h=1; h<=numCoppie; h++)
				coppie[h]->print();
			out << endl;
			
			for(int k=1; k<=numCoppie; k++)
				delete coppie[k];
		}
		
		if(tipo == "double")
		{
			chiamate = 0;
			double a, b;
			Coppia<double> *coppie[numCoppie+1];
			for(int j=1; j<=numCoppie; j++)
			{
				in >> c >> a >> b >> c;
				coppie[j] = new Coppia<double>(a, b);
			}
			
			buildHeap(coppie, numCoppie);
			int n = numCoppie;
			for(int j=1; j<=numCoppie; j++)
				extractMax(coppie, n);
			
			out << chiamate << " ";
			for(int h=1; h<=numCoppie; h++)
				coppie[h]->print();
			out << endl;
			
			for(int k=1; k<=numCoppie; k++)
				delete coppie[k];
		}
		
		if(tipo == "bool")
		{
			chiamate = 0;
			bool a, b;
			Coppia<bool> *coppie[numCoppie+1];
			for(int j=1; j<=numCoppie; j++)
			{
				in >> c >> a >> b >> c;
				coppie[j] = new Coppia<bool>(a, b);
			}
			
			buildHeap(coppie, numCoppie);
			int n = numCoppie;
			for(int j=1; j<=numCoppie; j++)
				extractMax(coppie, n);
			
			out << chiamate << " ";
			for(int h=1; h<=numCoppie; h++)
				coppie[h]->print();
			out << endl;
			
			for(int k=1; k<=numCoppie; k++)
				delete coppie[k];
		}
		
		if(tipo == "char")
		{
			chiamate = 0;
			char a, b;
			Coppia<char> *coppie[numCoppie+1];
			for(int j=1; j<=numCoppie; j++)
			{
				in >> c >> a >> b >> c;
				coppie[j] = new Coppia<char>(a, b);
			}
			
			buildHeap(coppie, numCoppie);
			int n = numCoppie;
			for(int j=1; j<=numCoppie; j++)
				extractMax(coppie, n);
			
			out << chiamate << " ";
			for(int h=1; h<=numCoppie; h++)
				coppie[h]->print();
			out << endl;
			
			for(int k=1; k<=numCoppie; k++)
				delete coppie[k];
		}
	}
	
	in.close();
	out.close();
	
	return 0;
}






