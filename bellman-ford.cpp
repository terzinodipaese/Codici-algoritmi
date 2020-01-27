#include <iostream>
#include <fstream>
#include <climits>

#define INF INT_MAX

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class T> class Graph
{
private:
	T *keys;				//array delle chiavi
	int indexK;				//numero di nodi presenti nel grafo
	int n;					//capacità nodi massima
	int **matricePesi;		//SE ESISTE, memorizza il peso di un arco, funge da matrice di adiacenza
							//ma memorizza i pesi dei nodi

	int *d;					//per ogni vertice/nodo, memorizza il peso del cammino minimo
							// dalla sorgente ad ogni altro nodo

	int *pred;				//array dei predecessori/genitori
	int m;					//numero di archi

public:
	Graph(int n)
	{
		this->n = n;
		indexK = m = 0;

		keys = new T[n];

		matricePesi = new int*[n];
		for(int i=0; i<n; i++)
		{
			matricePesi[i] = new int[n];
			for(int j=0; j<n; j++)
				matricePesi[i][j] = INF;
		}
			

		d = new int[n];

		pred = new int[n];
	}

	void insertKey(T key)
	{
		if(indexK < n)
		{
			keys[indexK] = key;
			indexK++;
			return;
		}

		return;
	}


	void initialize_single_source(T source)
	{
		int index_source = findIndex(source);

		for(int i=0; i<n; i++)
		{
			d[i] = INF;			//supponiamo che all'inizio che qualunque nodo non sia
								//raggiungibile dalla sorgente

			pred[i] = -1;		//supponiamo che all'inizio qualunque nodo non abbia genitore
		}


		if(index_source != -1)
			d[index_source] = 0;
	}

	void relax(int u, int v)
	{
		if(d[v] > d[u] + matricePesi[u][v] && d[u] != INF)
		{
			d[v] = d[u] + matricePesi[u][v];
			pred[v] = u;
		}
	}

	//se la procedura ritorna false, allora c'è un ciclo di peso negativo, altrimenti
	//ritorna true, allora vuol dire che non ci sono cicli di peso negativo
	bool bellman_ford(T source)
	{
		initialize_single_source(source);
		//eseguiamo i rilassamenti sui nodi esistenti
		for(int k=0; k<m; k++)
			for(int i=0; i<n; i++)
				for(int j=0; j<n; j++)
					if(matricePesi[i][j] != INF)
						relax(i, j);

		//per ogni arco nel grafo
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				if(matricePesi[i][j] != INF)
					if((d[j] > d[i] + matricePesi[i][j]) && d[i] != INF)
						return false;

		return true;
	}


	int findIndex(T key1)
	{
		for(int i=0; i<n; i++)
			if(keys[i] == key1)
				return i;

		return -1;
	}


	void insertEdge(T key1, T key2, int peso)
	{
		int index1 = findIndex(key1);
		int index2 = findIndex(key2);

		if(index1 == -1 || index2 == -1)
			return;
		if(matricePesi[index1][index2] == INF)
		{
			matricePesi[index1][index2] = peso;
			m++;
		}

		return;
	}

	int get_distance(int i) { return d[i]; }
};


int main()
{
	int auxi1, auxi2, nnodi, narchi, peso;
	double auxd1, auxd2;
	string tipo;
	char carattere;


	for(int i=0; i<100; i++)
	{
		in >> nnodi >> narchi;
		in >> tipo;

		if(tipo == "int")
		{
			Graph<int> myG(nnodi);

			for(int j=0; j<nnodi; j++)
			{
				in >> auxi1;
				myG.insertKey(auxi1);
			}

			//inseriamo archi con relativi pesi
			for(int j=0; j<narchi; j++)
			{
				in >> carattere >> auxi1 >> auxi2 >> peso >> carattere;
				myG.insertEdge(auxi1, auxi2, peso);
			}

			in >> auxi1 >> auxi2;

			int index_dest = myG.findIndex(auxi2);
			if(myG.bellman_ford(auxi1))
			{
				if(myG.get_distance(index_dest) != INF)
					out << myG.get_distance(index_dest) << endl;
				else
					out << "inf." << endl;
			}
			else
				out << "undef." << endl;
		}

		if(tipo == "double")
		{
			Graph<double> myG(nnodi);

			for(int j=0; j<nnodi; j++)
			{
				in >> auxd1;
				myG.insertKey(auxd1);
			}

			//inseriamo archi con relativi pesi
			for(int j=0; j<narchi; j++)
			{
				in >> carattere >> auxd1 >> auxd2 >> peso >> carattere;
				myG.insertEdge(auxd1, auxd2, peso);
			}

			in >> auxd1 >> auxd2;

			int index_dest = myG.findIndex(auxd2);
			if(myG.bellman_ford(auxd1))
			{
				if(myG.get_distance(index_dest) != INF)
					out << myG.get_distance(index_dest) << endl;
				else
					out << "inf." << endl;
			}
			else
				out << "undef." << endl;
		}
	}

	in.close();
	out.close();

	return 0;
}