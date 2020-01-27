/*
In questo esercizio le chiavi coincidono con gli indici, quindi non c'è bisogno
del metodo findIndex()
*/

#include <iostream>
#include <fstream>
#include <climits>

#define INF INT_MAX/2

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");



//in questo esercizio ci sono solo interi, quindi non farò una classe template
class Graph
{
private:
	int **matricePeso;			//svolge il ruolo della matrice di adicenza, ma memorizza i pesi degli archi;
	int *keys;					//memorizza le chiavi dei nodi;
	int n;						//capacità massima del grafo;
	int *d, *pred;				//d è array delle distanze dei cammini, pred è
								//è array dei predecessori;

	int indexKey;
	int m;						//numero di archi

public:
	Graph(int n)
	{
		this->n = n;
		keys = new int[n];
		d = new int[n];
		pred = new int[n];

		matricePeso = new int*[n];

		for(int i=0; i<n; i++)
		{
			matricePeso[i] = new int[n];
			for(int j=0; j<n; j++)
				matricePeso[i][j] = INF;
		}

		indexKey = 0;
		m = 0;
	}

	//in questo caso s è un'indice dell'array, non una chiave(IN REALTà, le due cose coincidono)
	void initialise_ss(int s)
	{
		for(int i=0; i<n; i++)
		{
			d[i] = INF;
			pred[i] = -1;
		}

		d[s] = 0;
	}

	void insertKey(int key)
	{
		if(indexKey < n)
		{
			keys[indexKey] = key;
			indexKey++;
			return;
		}

		return;
	}

	void relax(int u, int v)
	{
		if(d[v] > d[u] + matricePeso[u][v] && d[u] != INF)
			d[v] = d[u] + matricePeso[u][v];
	}

	void insertEdge(int key1, int key2, int peso)
	{
		if(key1 == -1 || key2 == -1)
			return;

		matricePeso[key1][key2] = peso;
		m++;
	}

	//versione modificata della bellman_ford originale;
	//il metodo restituisce il peso del cammino da source a dest
	//dopo K iterazioni del ciclo principale;
	int bellman_ford(int source, int dest, int K)
	{
		initialise_ss(source);

		for(int i=0; i<K; i++)
			for(int u=0; u<n; u++)
				for(int v=0; v<n; v++)
					if(matricePeso[u][v] != INF)
						relax(u, v);

		return d[dest];
	}


};


int main()
{
	int N, M, K;
	int x, y, peso;
	char carattere;

	for(int i=0; i<100; i++)
	{
		in >> N >> M >> K;
		Graph myG(N);

		for(int j=0; j<N; j++)
			myG.insertKey(i);

		for(int j=0; j<M; j++)
		{
			in >> carattere >> x >> y >> peso >> carattere;
			myG.insertEdge(x, y, peso);
		}

		in >> x >> y;

		if(myG.bellman_ford(x, y, K) == INF)
			out << "inf." << endl;
		else
			out << myG.bellman_ford(x, y, K) << endl;
	}

	in.close();
	out.close();

	return 0;
}