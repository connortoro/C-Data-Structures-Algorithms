/****************
Template created by Kazumi Slott
CS311

Your name: Connor Toro
Your programmer number: 31
Hours spent?: 5
Any difficulties?: nope
*****************/

#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <class T>
class AVL;

//Node class
template <class T>
class Node
{
    friend class AVL<T>;
    private:
        T el;
        Node* right;
        Node* left;
        Node* up;
        int bf;
    public:
        Node() {up = right = left = NULL; bf = 0;};
        Node(const T& e){up = right = left = NULL; el = e; bf = 0;};
        T getEl() const {return el;}
};

//AVL Class
template <class T>
class AVL
{
private:
    Node<T>* root;
    void destroy(Node<T>* p);
    void inOrderPrint(Node<T>* p);
    int getMaxLength(Node<T>* p);
    Node<T>* rightRotation(Node<T>* P);
    Node<T>* leftRotation(Node<T>* P);
    void balanceTree(Node<T>* newNode);
    Node<T>* updateBF(Node<T>* Q);
public:
    AVL() {root = NULL;} //implement constructor here
    ~AVL(); //need to have a private recursive function. Name it destroy.
    void insertNodeI(const T& e);
    void inOrderPrint();
    void BFTprint();
    int getMaxLength();
};


//Delete
template <class T>
AVL<T>::~AVL()
{
  destroy(root);
}

template <class T>
void AVL<T>::destroy(Node<T>* p)
{
  if(p == NULL) return;
  destroy(p->left);
  destroy(p->right);
  delete p;
}

//In-Order Print
template <class T>
void AVL<T>::inOrderPrint()
{
 inOrderPrint(root);
}

template <class T>
void AVL<T>::inOrderPrint(Node<T>* p)
{
  if(p == NULL) return;
  inOrderPrint(p->left);
  cout << p->el << "-->";
  inOrderPrint(p->right);
}

//Max Length
template <class T>
int AVL<T>::getMaxLength()
{
  getMaxLength(root);
}

template <class T>
int AVL<T>::getMaxLength(Node<T>* p) //private function. Why?
{
  if(p == NULL) return 0;
  return max(getMaxLength(p->left), getMaxLength(p->right)) + 1;
}

//BFT Print
template <class T>
void AVL<T>::BFTprint()
{
  queue<Node<T>*> q;
  q.push(root);
  while(!q.empty()) {
    Node<T>* temp = q.front();
    q.pop();
    if(temp == root) {
      cout << temp->el  << " " << temp->bf << " -->";
    } else {
      cout << temp->el << " " << temp->bf << " " << temp->up->el << "-->";
    }
    if(temp->left != NULL) q.push(temp->left);
    if(temp->right != NULL) q.push(temp->right);
  }
}

//Insert Node Iteratively
template <class T>
void AVL<T>::insertNodeI(const T& e)
{
  Node<T>* newNode = new Node<T>(e);
  Node<T>* p = root;
  Node<T>* parent = NULL;
  while(p != NULL)
  {
    parent = p;
    if(e < p->el)
	  p = p->left;
    else
	  p = p->right;
  }
  if(parent == NULL) {
    root = newNode;
    return;
   } else if(e < parent->el)
    parent->left = newNode;
  else
    parent->right = newNode;

  newNode->up = parent;
  balanceTree(newNode);
}

/*-----------------------------AVL-FUNCTIONS-----------------------------------*/

//Balance Tree
template <class T>
void AVL<T>::balanceTree(Node<T>* newNode)
{
    bool isRoot = false;
    bool isLeft = false;
    Node<T>* P = updateBF(newNode);
    if(P == NULL) return;
    if(P == root)
        isRoot = true;
    else if(P->up->left == P)
        isLeft = true;
    Node<T>* newRoot;

    //LL
    if(P->bf == 2 && P->left != NULL && P->left->bf == 1) {
        newRoot = rightRotation(P);
    }

    //RR
    if(P->bf == -2 && P->right != NULL && P->right->bf == -1) {
        newRoot = leftRotation(P);
    }

    //LR
    if(P->bf == 2 && P->left != NULL && P->left->bf == -1) {
        P->left = leftRotation(P->left);
        newRoot = rightRotation(P);
    }

    //RL
    if(P->bf == -2 && P->right != NULL && P->right->bf == 1) {
        P->right = rightRotation(P->right);
        newRoot = leftRotation(P);
    }

    if(isRoot)
        root = newRoot;
    else if(isLeft)
        newRoot->up->left = newRoot;
    else
        newRoot->up->right = newRoot;
}

//Update Balance Factor
template <class T>
Node<T>* AVL<T>::updateBF(Node<T>* Q)
{
    Node<T>* P = Q->up;
    if(P->left == Q) {
        P->bf++;
    } else {
        P->bf--;
    }

    while(P != root && P->bf != 2 && P->bf != -2) {
        Q = P;
        P = P->up;
        if(Q->bf == 0) return NULL;
        if(P->left == Q) {
            P->bf++;
        } else {
            P->bf--;
        }
    }
    if(P->bf == 2 || P->bf == -2) {
        return P;
    }
    return NULL;
}

//Right Rotation
template <class T>
Node<T>* AVL<T>::rightRotation(Node<T>* P)
{
    Node<T>* root = P->left;
    root->up = P->up;
    P->up = root;
    P->left = root->right;
    if(root->right != NULL)
        root->right->up = P;
    root->right = P;

    root->bf = getMaxLength(root->left)-getMaxLength(root->right);
    P->bf = getMaxLength(P->left)-getMaxLength(P->right);

    return root;
}

//Left Rotation
template <class T>
Node<T>* AVL<T>::leftRotation(Node<T>* P)
{
    Node<T>* root = P->right;
    root->up = P->up;
    P->up = root;
    P->right = root->left;
    if(root->left != NULL)
        root->left->up = P;
    root->left = P;

    root->bf = getMaxLength(root->left)-getMaxLength(root->right);
    P->bf = getMaxLength(P->left)-getMaxLength(P->right);

    return root;
}

#endif
