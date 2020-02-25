#include <iostream>
#include <fstream>
#include <string>
#define inf INT_MAX/2

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

class MPriorityIndexQueue{
private:
    int *I,*Q;
    int heapsize;
    
    int Left(int i){return i<<1;}
    int Right(int i){return (i<<1)|1;}
    int Parent(int i){return i>>1;}
    
    void Heapify(int x){
        int y= Left(x),w=Right(x), max=x;
        
        if(y<=heapsize && Q[I[max]]>Q[I[y]]) max=y;
        if(w<=heapsize && Q[I[max]]>Q[I[w]]) max=w;
        
        if(max!=x){
            I[0]=I[max];
            I[max]=I[x];
            I[x]=I[0];
            Heapify(max);
        }
        
    }
    
    
    
public:
    MPriorityIndexQueue(int* q,int size){
        Q=q;
        heapsize=size;
        I=new int[size+1];
        
        for (int i=1; i<=size; i++) I[i]=i-1;
        BuildHeap();
    }
    void BuildHeap(){
        for (int i=heapsize/2; i>0; i--) {
            Heapify(i);
        }
    }
    int ExtractMin(){
        if(heapsize<1) return-1;
        
        I[0]=I[heapsize];
        I[heapsize]=I[1];
        I[1]=I[0];
        
        heapsize--;
        Heapify(1);
        
        return I[heapsize+1];
    }
    
};

template <class T>
class MGraph{
private:
    
    T** K;
    int** M;
    int len,n,m;
    int *d,*p;
    
    int findIndex(T v){
        for (int i=0; i<n; i++)
            if(*K[i]==v) return i;
        return -1;
    }
    
    void InitializeSingleSource(int s){
        d=new int[n];
        p=new int[n];
        for (int i=0; i<n; i++) {
            d[i]=inf;
            p[i]=-1;
        }
        d[s]=0;
    }
    
    void RELAX(int u, int v){
        if(d[v]>d[u]+M[u][v]){
            d[v]=d[u]+M[u][v];
            p[v]=u;
        }
    }
    
    void SCAN(int u){
        for (int v=0; v<n; v++)
            if(M[u][v]<inf) RELAX(u,v);
    }
    
    void Dijkstra(int s){
        InitializeSingleSource(s);
        MPriorityIndexQueue Q(d,n);
        int v;
        for (int i=0; i<n; i++) {
            v=Q.ExtractMin();
            SCAN(v);
            Q.BuildHeap();
        }
    }
    
public:
    
    MGraph(int l){
        n=m=0;
        len=l;
        
        M=new int*[l];
        K=new T*[l];
        
        for (int i=0; i<l; i++) {
            M[i]=new int[l];
            for (int j=0; j<l; j++)M[i][j]=inf;
            K[i]=NULL;
        }
    }
    
    ~MGraph(){
        for (int i=0; i<n; i++) {
            delete[] M[i];
            delete K[i];
        }
        delete[] K;
        delete[] M;
    }
    
    void addNode(T v){
        if (n==len)return;
        if (findIndex(v)>-1) return;
        
        K[n]=new T(v);
        n++;
        
    }
    
    void addEdge(T x, T y,int p){
        int i=findIndex(x);
        int j=findIndex(y);
        
        if(i<0 || j<0) return;
        M[i][j]=p;
        m++;
        
    }
    
    int ShortestPath(T s, T v){
        int i =findIndex(s);
        int j=findIndex(v);
        
        if(i<0 || j<0) return inf;
        Dijkstra(i);
        return d[j];
    }
    
    void print(){
        for (int i =0; i<n; i++) {
            cout<<"["<<*K[i]<<": ";
            for (int j=0; j<n; j++)
                if (M[i][j]<inf)
                    cout<<"("<<*K[j]<<", "<<M[i][j]<<"); ";
            cout<<"]"<<endl;
        }
    }
};

template <class T>
void esegui(T s, int N, int M){
    MGraph<T> grafo(N);
    int P;
    char c; T v;
    for (int i=0; i<N; i++) {
        fin>>s;
        grafo.addNode(s);
    }
    for (int i=0; i<M; i++) {
        fin>>c>>s>>v>>P>>c;
        grafo.addEdge(s, v, P);
    }
    fin>>s>>v;
    //grafo.print();
    int d=grafo.ShortestPath(s, v);
    if(d<inf)fout<<d;
    else fout<<"inf.";
    fout<<endl;
}

int main(){
    string S;
    int n,m;
    for (int i =0; i<100; i++) {
        fin>>n>>m>>S;
        if(S[0]=='i')esegui(int(0), n, m);
        else esegui(double(0.0), n, m);
    }
    return 0;
}
