#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <typename N> class Node
{
private:
	N key;
	Node<N> *parent, *left, *right;

public:
	Node(N key)
	{
		this->key = key;
		left = right = parent = NULL;
	}
	
	void setKey(N key) { this->key = key; }
	void setRight(Node<N> *right) { this->right = right; }
	void setLeft(Node<N> *left) { this->left = left; }
	void setParent(Node<N> *parent) { this->parent = parent; }
	
	N getKey() const { return key; }
	Node<N>* getRight() const { return right; }
	Node<N>* getLeft() const { return left; }
	Node<N>* getParent() const { return parent; }
};

template <typename B> class BST
{
private:
	int n;
	Node<B> *root;

	void aux_inorder(Node<B> *node, ofstream &out)
	{
		if(node)
		{
			aux_inorder(node->getLeft(), out);
			out << node->getKey() << " ";
			aux_inorder(node->getRight(), out);
		}
	}
	
	void aux_preorder(Node<B> *node, ofstream &out)
	{
		if(node)
		{
			out << node->getKey() << " ";
			aux_preorder(node->getLeft(), out);
			aux_preorder(node->getRight(), out);
		}
	}
	
	B minimo(Node<B> *node)
	{
		if(node)	
		{
			while(node->getLeft())
				node = node->getLeft();
		}
		
		if(node)
			return node->getKey();
		else
			return -1;
	}
	
	
	void aux_postorder(Node<B> *node, ofstream &out)
	{
		if(node)
		{
			aux_postorder(node->getLeft(), out);
			aux_postorder(node->getRight(), out);
			out << node->getKey() << " ";
		}
	}
	
public:
	BST()
	{
		n = 0;
		root = NULL;
	}
	
	Node<B>* getRoot() { return root; }
	
	void inorder(ofstream &out) { aux_inorder(root, out); }
	void preorder(ofstream &out) { aux_preorder(root, out); }
	void postorder(ofstream &out) { aux_postorder(root, out); }
	
	void insert(B key)
	{
		Node<B> *node = root;
		Node<B> *parent = NULL;
		
		while(node != NULL)			//serve a impostare il parent
		{
			parent = node;
			if(key > node->getKey())
				node = node->getRight();
			else
				node = node->getLeft();
		}
		
		Node<B> *newnode = new Node<B>(key);
		n++;
		
		if(parent == NULL)
		{
			root = newnode;
			return;
		}
		
		
		newnode->setParent(parent);
		if(key <= parent->getKey())
			parent->setLeft(newnode);
		else
			parent->setRight(newnode);
	
	}
	
	B getSuccessor(B key)
	{
		Node<B> *temp_node = search(root, key);		//cerchiamo il nodo di cui trovare il successore
		if(temp_node)								//se esiste
		{
			if(temp_node->getRight())			//se esiste il figlio destro "caso banale"
				return minimo(temp_node->getRight());
			
			Node<B> *parent = temp_node->getParent();	//ottengo il genitore del nodo da cancellare
			while(parent != NULL && temp_node == parent->getRight())
			{
				temp_node = parent;
				parent = parent->getParent();
			}
			
			if(parent)
				return parent->getKey();
			else
				return -1;
		}
	}
	
	Node<B>* search(Node<B> *node, B key)
	{
		if(node == NULL || node->getKey() == key)
			return node;
		if(key > node->getKey())
			search(node->getRight(), key);
		else
			search(node->getLeft(), key);
	}
	
	void canc(Node<B> *x, B key)
	{
		Node<B> *temp = search(x, key);		//cerca un nodo con la chiave key
		if(temp == NULL)					//se non viene trovato, usciamo perchè un nodo inesistente non può essere cancellato
			return;
		
		Node<B> *parent = temp->getParent();		//otteniamo il genitore del nodo da cancellare
		if(!temp->getLeft() || !temp->getRight())	//gestisce i casi 1 & 2: 0 oppure 1 solo figlio, caso "facile"
		{
			n--;									//decrementiamo il contatore dei nodi
			Node<B> *son = temp->getRight();		
			if(temp->getLeft())
				son = temp->getLeft();
			
			if(!parent)				//in un BST l'unico nodo che non ha padre è la radice
				root = son;
			else					//colleghiamo il parent al son, cioè il colleghiamo nonno e nipote, scavalcando temp
			{
				if(temp == parent->getLeft())
					parent->setLeft(son);
				else
					parent->setRight(son);
			}
			
			if(son)
				son->setParent(parent);
		
		}
		
		else									//caso 3: due figli
		{
			B next = this->getSuccessor(temp->getKey());		//cerchiamo l'immediato successore di temp
			Node<B> *succ = new Node<B>(next);
			temp->setKey(succ->getKey());						//temp assumerà la chiave del suo immediato successore
			canc(temp->getRight(), succ->getKey());				//cancelliamo l'immediato successore di temp
		}
		
	}
	
	void LRotate(Node<B> *x)
	{
		if(x->getRight() != NULL)
		{
			Node<B> *y = x->getRight();
			x->setRight(y->getLeft());
		
			if(y->getLeft() != NULL)
				y->getLeft()->setParent(x);
		
			y->setParent(x->getParent());
		
			if(x->getParent() == NULL)
				root = y;
			else if(x == x->getParent()->getLeft())
				x->getParent()->setLeft(y);
			else
				x->getParent()->setRight(y);
		
			y->setLeft(x);
			x->setParent(y);
		}
	}
		
	void RRotate(Node<B> *x)
	{
		if(x->getLeft() != NULL)
		{
			Node<B> *y = x->getLeft();
			x->setLeft(y->getRight());
		
			if(y->getRight() != NULL)
				y->getRight()->setParent(x);
		
			y->setParent(x->getParent());
		
			if(x->getParent() == NULL)
				root = y;
			else if(x == x->getParent()->getLeft())
				x->getParent()->setLeft(y);
			else
				x->getParent()->setRight(y);
		
			y->setRight(x);
			x->setParent(y);
		}
	}
};



int main()
{
	string visita, tipo, operazione;
	int N, nRot;
	int auxi;
	double auxd; 
	
	
	for(int i=0; i<100; i++)
	{
		in >> tipo >> N >> nRot >> visita;
		
		if(tipo == "int")
		{
			BST<int> myBST;
			
			for(int j=0; j< N; j++)
			{
				in >> operazione;
				if(operazione[0] == 'i')
				{
					operazione = operazione.substr(4);
					auxi = atoi(operazione.c_str());
					myBST.insert(auxi);
				}
				
				else
				{
					operazione = operazione.substr(5);
					auxi = atoi(operazione.c_str());
					myBST.canc(myBST.getRoot(), auxi);
				}
			}
			
			for(int k=0; k<nRot; k++)
			{
				in >> operazione;
				if(operazione[0] == 'l')
				{
					operazione = operazione.substr(5);
					auxi = atoi(operazione.c_str());
					Node<int> *appoggio = myBST.search(myBST.getRoot(), auxi);
					
					myBST.LRotate(appoggio);
				}
				
				else
				{
					operazione = operazione.substr(6);
					auxi = atoi(operazione.c_str());
					Node<int> *appoggio = myBST.search(myBST.getRoot(), auxi);
					
					myBST.RRotate(appoggio);
				}
			}
			
			if(visita == "inorder")
				myBST.inorder(out);
			if(visita == "preorder")
				myBST.preorder(out);
			if(visita == "postorder")
				myBST.postorder(out);
			
			out << endl;
		}
		
		
		if(tipo == "double")
		{
			BST<double> myBST;
			
			for(int j=0; j< N; j++)
			{
				in >> operazione;
				if(operazione[0] == 'i')
				{
					operazione = operazione.substr(4);
					auxd = atof(operazione.c_str());
					myBST.insert(auxd);
				}
				
				else
				{
					operazione = operazione.substr(5);
					auxd = atof(operazione.c_str());
					myBST.canc(myBST.getRoot(), auxd);
				}
			}
			
			for(int k=0; k<nRot; k++)
			{
				in >> operazione;
				if(operazione[0] == 'l')
				{
					operazione = operazione.substr(5);
					auxd = atof(operazione.c_str());
					Node<double> *appoggio = myBST.search(myBST.getRoot(), auxd);
					
					myBST.LRotate(appoggio);
				}
				
				else
				{
					operazione = operazione.substr(6);
					auxd = atof(operazione.c_str());
					Node<double> *appoggio = myBST.search(myBST.getRoot(), auxd);
					
					myBST.RRotate(appoggio);
				}
			}
			
			if(visita == "inorder")
				myBST.inorder(out);
			if(visita == "preorder")
				myBST.preorder(out);
			if(visita == "postorder")
				myBST.postorder(out);
			
			out << endl;
		}
	}
	
	in.close();
	out.close();
	
	return 0;
}




