#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


class Coppia
{
private:
	float x, y;		//x primo valore della coppia, y è il secondo
	
public:
	float getX() { return x; }
	float getY() { return y; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
};


//versione della classe Coppia, ma con x intera
class ICoppia
{
private:
	int x;		//x è il primo valore della coppia, y è il secondo
	float y;
	
public:
	int IgetX() { return x; }
	float IgetY() { return y; }
	void IsetX(int x) { this->x = x; }
	void IsetY(float y) { this->y = y; }
};

int findMax(ICoppia *arr, int len)
{
	int max = arr[0].IgetX();
	
	for(int i=0; i<len; i++)
		if(arr[i].IgetX() > max)
			max = arr[i].IgetX();
		
	return max;
}

int findMin(ICoppia *arr, int len)
{
	int min = arr[0].IgetX();
	
	for(int i=0; i<len; i++)
		if(arr[i].IgetX() < min)
			min = arr[i].IgetX();
		
	return min;
}

void countingSort(Coppia *a, int len)
{
	ICoppia appoggio[len];
	for(int i=0; i<len; i++)
	{
		appoggio[i].IsetX(a[i].getX() * 10);
		appoggio[i].IsetY(a[i].getY());
	}
	
	int min = findMin(appoggio, len);
	int max = findMax(appoggio, len);
	int k = max - min + 1;
	
	
	ICoppia b[len];
	for(int t=0; t<len; t++)
		b[t].IsetY(a[t].getY());
	
	
	int c[k];
	
	for(int i=0; i<k; i++)
		c[i] = 0;
	
	for(int i=0; i<len; i++)
		c[appoggio[i].IgetX() - min]++;
	
	for(int i=1; i<k; i++)
		c[i] = c[i] + c[i-1];
	
	for(int i=len-1; i>=0; i--)
	{
		b[c[appoggio[i].IgetX() - min]-1].IsetX(appoggio[i].IgetX());
		b[c[appoggio[i].IgetX() - min]-1].IsetY(appoggio[i].IgetY());
		
		c[appoggio[i].IgetX() - min]--;
	}
	
	for(int i=0; i<k; i++)
		out << c[i] << " ";
	
	for(int i=0; i<len; i++)
		out << "(" << (double)b[i].IgetX()/10 << " " << b[i].IgetY() << ") ";
	
	out << endl;
}

int main()
{
	int N;
	char c;
	float supporto1, supporto2;
	
	//ciclo sulle righe
	for(int count=0; count<100; count++)
	{
		in >> N;
		Coppia coppie[N];
		
		//ciclo sulle coppie di una riga
		for(int i=0; i<N; i++)
		{
			in >> c >> supporto1 >> supporto2 >> c;
			coppie[i].setX(supporto1);
			coppie[i].setY(supporto2);
		}
		
		countingSort(coppie, N);
	}
	
	in.close();
	out.close();
	
	return 0;
}



