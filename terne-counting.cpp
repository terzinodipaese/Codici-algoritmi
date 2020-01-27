#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

class Terna
{
private:
	float x, y, z;
	
public:
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	void setZ(float z) { this->z = z; }
};


//versione della classe Coppia, ma con x intera
class ITerna
{
private:
	int x;		//x è il primo valore della coppia, y è il secondo
	float y;
	float z;
	
public:
	int IgetX() { return x; }
	float IgetY() { return y; }
	float IgetZ() { return z; }
	void IsetX(int x) { this->x = x; }
	void IsetY(float y) { this->y = y; }
	void IsetZ(float z) { this->z = z; }
};


int findMax(ITerna *arr, int len)
{
	int max = arr[0].IgetX();
	
	for(int i=0; i<len; i++)
		if(arr[i].IgetX() > max)
			max = arr[i].IgetX();
		
	return max;
}

int findMin(ITerna *arr, int len)
{
	int min = arr[0].IgetX();
	
	for(int i=0; i<len; i++)
		if(arr[i].IgetX() < min)
			min = arr[i].IgetX();
		
	return min;
}


void countingSort(Terna *a, int len)
{
	ITerna appoggio[len];
	for(int i=0; i<len; i++)
	{
		appoggio[i].IsetX(a[i].getX() * 10);
		appoggio[i].IsetY(a[i].getY());
		appoggio[i].IsetZ(a[i].getZ());
	}
	
	int min = findMin(appoggio, len);
	int max = findMax(appoggio, len);
	int k = max - min + 1;
	
	
	ITerna b[len];
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
		b[c[appoggio[i].IgetX() - min]-1].IsetZ(appoggio[i].IgetZ());
		
		c[appoggio[i].IgetX() - min]--;
	}
	
	for(int i=0; i<k; i++)
		out << c[i] << " ";
	
	for(int i=0; i<len; i++)
		out << "(" << (double)b[i].IgetX()/10 << " " << b[i].IgetY() << " " << b[i].IgetZ() << ") ";
	
	out << endl;
}



int main()
{
	int N;
	char c;
	float supporto1, supporto2, supporto3;
	
	//ciclo sulle righe
	for(int count=0; count<100; count++)
	{
		in >> N;
		Terna terne[N];
		
		//ciclo sulle coppie di una riga
		for(int i=0; i<N; i++)
		{
			in >> c >> supporto1 >> supporto2 >> supporto3 >> c;
			terne[i].setX(supporto1);
			terne[i].setY(supporto2);
			terne[i].setZ(supporto3);
		}
		
		countingSort(terne, N);
	}
	
	in.close();
	out.close();
	
	return 0;
}




