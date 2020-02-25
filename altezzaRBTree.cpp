#include <iostream>
#include <fstream>
#include <string>
#define R 0
#define B 1

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

template<class T>
class Nodo{
private:
    Nodo<T> *padre, *sinistro, *destro;
    T val;
    short color;
public:
    Nodo(T v){
        val=v;
        padre=destro=sinistro=NULL;
        color=R;
    }
    
    //GET
    Nodo<T>* getPadre(){return padre;}
    Nodo<T>* getSinistro(){return sinistro;}
    Nodo<T>* getDestro(){return destro;}
    
    T getVal(){return val;}
    short getColor(){return color;}
    
    //SET
    void setPadre(Nodo<T>* x){padre=x;}
    void setSinistro(Nodo<T>* x){sinistro=x;}
    void setDestro(Nodo<T>* x){destro=x;}
    
    void setVal(T v){val=v;}
    void setColor(short c){color=c; }
};

template<class T>
class RBTree{
private:
    Nodo<T>* root;
    
    void LeftRotate(Nodo<T>* x){
        Nodo<T>* y=x->getDestro();
        
        x->setDestro(y->getSinistro());
        if(x->getDestro()!=NULL)x->getDestro()->setPadre(x);
        
        y->setPadre(x->getPadre());
        if(y->getPadre()==NULL)root=y;
        else if(x==y->getPadre()->getDestro()) y->getPadre()->setDestro(y);
        else y->getPadre()->setSinistro(y);
        
        y->setSinistro(x);
        x->setPadre(y);
    }
    
    void RigthRotate(Nodo<T>* y){
        Nodo<T>* x=y->getSinistro();
        
        y->setSinistro(x->getDestro());
        if(y->getSinistro()!=NULL)y->getSinistro()->setPadre(y);
        
        x->setPadre(y->getPadre());
        if (x->getPadre()==NULL)root=x;
        else if(y==x->getPadre()->getSinistro()) x->getPadre()->setSinistro(x);
        else x->getPadre()->setDestro(x);
        
        x->setDestro(y);
        y->setPadre(x);
    }
    
    void fixupRBTree(Nodo<T>*);
    
    int altezza(Nodo<T>* x){
        if(x==NULL)return 0;
        else {
            int a=altezza(x->getDestro());
            int b=altezza(x->getSinistro());
            return ((a>b? a:b)+1);
        }
    }
    
public:
    RBTree():root(NULL){};
    
    int altezza(){return altezza(root);}
    
    void addNode(T v){
        Nodo<T>* nuovo=new Nodo<T>(v);
        Nodo<T>* x=root,*y=NULL;
        
        while (x!=NULL) {
            y=x;
            
            if (x->getVal()>v) x=x->getSinistro();
            else x=x->getDestro();
        }
        
        nuovo->setPadre(y);
        if(y==NULL)root=nuovo;
        else if(y->getVal()>v) y->setSinistro(nuovo);
        else y->setDestro(nuovo);
        
        fixupRBTree(nuovo);
    }
    
    
};

template<class T>
void esegui(T k){
    int N;
    fin>>N;
    
    RBTree<T> albero;
    for (int i=0; i<N; i++) {
        fin>>k;
        albero.addNode(k);
    }
    
    fout<<albero.altezza()<<endl;
    
}

int main(){
    string S;
    for (int count=0; count<100; count++) {
        fin>>S;
        if(S=="int")esegui(int(0));
        else esegui(double(0.0));
    }
    return 0;
}

template<class T>
void RBTree<T>::fixupRBTree(Nodo<T>* z){
    
    while (z->getPadre()!=NULL && z->getPadre()->getColor()==R) {
        if (z->getPadre()==z->getPadre()->getPadre()->getSinistro()) {
            Nodo<T>* y=z->getPadre()->getPadre()->getDestro();
            
            if(y!=NULL && y->getColor()==R){
                y->setColor(B);
                y->getPadre()->setColor(R);
                z->getPadre()->setColor(B);
                z=y->getPadre();
            }
            else{
                if(z==z->getPadre()->getDestro()){
                    z=z->getPadre();
                    LeftRotate(z);
                }
                z->getPadre()->setColor(B);
                z->getPadre()->getPadre()->setColor(R);
                RigthRotate(z->getPadre()->getPadre());
            }
        }
        else{
            Nodo<T>* y=z->getPadre()->getPadre()->getSinistro();
            
            if(y!=NULL && y->getColor()==R){
                y->setColor(B);
                y->getPadre()->setColor(R);
                z->getPadre()->setColor(B);
                z=y->getPadre();
            }
            else{
                if(z==z->getPadre()->getSinistro()){
                    z=z->getPadre();
                    RigthRotate(z);
                }
                z->getPadre()->setColor(B);
                z->getPadre()->getPadre()->setColor(R);
                LeftRotate(z->getPadre()->getPadre());
            }
        }
    }
    
    root->setColor(B);
}
