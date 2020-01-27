#include <iostream>
#include <fstream>

using namespace std;


ifstream in("input.txt");
ofstream out("output.txt");

class Activity
{
public:
	int s, f;		//tempo di inizio e fine attività
};


void merge(Activity *arr, int left, int c, int right)
{
	int i=left, j=c+1;
	int k=0;
	
	Activity b[right+1];
	
	
	while((i<=c) && (j<=right))
	{
		if(arr[i].f <= arr[j].f)
		{
			b[k] = arr[i];
			i++;
		}
		
		else
		{
			b[k] = arr[j];
			j++;
		}
		
		k++;
	}
	
	//se sono rimasti elementi dal 1o sottoarray
	while(i <= c)
	{
		b[k] = arr[i];
		i++;
		k++;
	}
	
	//se sono rimasti elementi dal 2o sottoarray
	while(j <= right)
	{
		b[k] = arr[j];
		j++;
		k++;
	}
	
	
	//trasferiamo gli elementi ordinati da b in arr
	//che quindi conterrà ora gli elementi ordinati
	for(int t=left; t <= right; t++)
		arr[t] = b[t-left];
}


//prende un'array di attività
void mergesort(Activity *arr, int left, int right)
{
	if(left < right)
	{
		int c = (left+right)/2;
		mergesort(arr, left, c);
		mergesort(arr, c+1, right);
		merge(arr, left, c, right);
	}
}

int greedy_activity(Activity *a, int len)
{
	//ordiniamo attraverso mergesort in base ai tempi di fine
	mergesort(a, 0, len-1);			
	
	//ci sarà almeno un'attività
	int num = 1;
	
	//k tiene traccia della k-esima attività
	int k = 0;
	
	for(int i=1; i<len; i++)
	{
		if(a[i].s >= a[k].f)
		{
			num++;
			k = i;
		}
	}
	
	//ritorniamo la cardinalità dell'insieme di attività compatibili
	return num;
}


int main()
{
	int start, finish;
	int nAtt;
	char carattere;
	
	//ciclo sulle righe
	for(int count=0; count<100; count++)
	{
		in >> nAtt;		//leggiamo numero di attività
		Activity l[nAtt];		//creamo l'array delle attività
		
		//di volta in volta leggiamo inizio e fine della t-esima attività
		for(int t=0; t<nAtt; t++)
		{
			in >> carattere >> start >> finish >> carattere;
			l[t].s = start;
			l[t].f = finish;
		}
		
		out << greedy_activity(l, nAtt) << endl;
	}
	
	in.close();
	out.close();
	
	return 0;
}


















