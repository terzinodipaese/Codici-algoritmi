#include <iostream>
#include <fstream>
#include <string>
#define R 0
#define B 1

using namespace std;

ifstream fin ("input.txt");
ofstream fout ("output.txt");

template<class T>
class Nodo{
private:
    T* val;
    Nodo<T> *sinistro, *destro, *padre;
    short color;
public:
    Nodo(T v){
        val = new T(v);
        sinistro=padre=destro=NULL;
        color=R;
    }
    ~Nodo(){delete val;}
    
    //GET
    Nodo<T>* getPadre(){return padre;}
    Nodo<T>* getDestro(){return destro;}
    Nodo<T>* getSinistro(){return sinistro;}
    
    short getColor(){return color;}
    T getVal(){return *val;}
    
    //SET
    void setPadre(Nodo<T>* x){padre=x;}
    void setDestro(Nodo<T>* x){destro=x;}
    void setSinistro(Nodo<T>* x){sinistro=x;}
    
    void setColor(short c){color=c;}
    void setVal(T x){return *val=x;}
    
    void swap(Nodo<T> x){
        T *supp=x.val;
        x.val=this->val;
        this->val=supp;
    }
    
    void stampa(){
        fout<<"("<<*val<<" "<<(color==R? 'R':'B')<<") ";
    }
};

template<class T>
class RBTree{
private:
    Nodo<T>* root;
    
    void preorder(Nodo<T>* x){
        if(x!=NULL){
            x->stampa();
            preorder(x->getSinistro());
            preorder(x->getDestro());
        }
    }
    void inorder(Nodo<T>* x){
        if(x!=NULL){
            inorder(x->getSinistro());
            x->stampa();
            inorder(x->getDestro());
        }
    }
    void postorder(Nodo<T>* x){
        if(x!=NULL){
            postorder(x->getSinistro());
            postorder(x->getDestro());
            x->stampa();
        }
    }
    
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
    
    void RBTreeFixup(Nodo<T>*);
    
public:
    RBTree(){root =NULL;}
    
    void AddNode(T v){
        Nodo<T>* nuovo= new Nodo<T>(v);
        Nodo<T>* x=root, *y=NULL;
        
        while (x!=NULL) {
            y=x;
            if(x->getVal()>v)x=x->getSinistro();
            else x=x->getDestro();
        }
        nuovo->setPadre(y);
        if(y==NULL)root=nuovo;
        else if (y->getVal()>v)y->setSinistro(nuovo);
        else y->setDestro(nuovo);
        
        RBTreeFixup(nuovo);
    }
    
    
    void Stampa(string s){
        if(s[1]=='n')inorder(root);
        else if(s[1]=='r')preorder(root);
        else postorder(root);
    }
};

template<class T>
void esegui(T k){
    int N; string S;
    fin>>N>>S;
    
    RBTree<T>* albero=new RBTree<T>();
    
    for (int i=0; i<N; i++) {
        fin>>k;
        albero->AddNode(k);
        
        //albero->Stampa(S);
        //cout<<endl<<endl;
    }
    
    albero->Stampa(S);
    fout<<endl;
    
}

int main(){
    string S;
    for (int count=0; count<100 ; count++) {
        fin>>S;
        if(S=="int") esegui(int(0));
        else esegui(double(0.0));
    }
    
    return 0;
}

template<class T>
void RBTree<T>::RBTreeFixup(Nodo<T>* z){
    
    while (z!=root && z->getPadre()->getColor()==R) {
        
        if(z->getPadre()==z->getPadre()->getPadre()->getSinistro()){
            
            Nodo<T>* y=z->getPadre()->getPadre()->getDestro();
            
            if(y!=NULL && y->getColor()==R){
                z->getPadre()->setColor(B);
                y->setColor(B);
                y->getPadre()->setColor(R);
                
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
                z->getPadre()->setColor(B);
                y->setColor(B);
                y->getPadre()->setColor(R);
                
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
