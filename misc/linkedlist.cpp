#include <iostream>
using namespace std;

//---------------------------NODE CLASS--------------------------------------
template <class T>
class Node {
public:
	//Instance Variables
	T data;
	Node* next;

	//Constructor
	Node(const T& value) : data(value), next(nullptr) {}
};

//------------------------LINKED LIST CLASS-----------------------------------
template <class T>
class LinkedList {
private:
	Node<T>* head;

public:
	LinkedList() : head(nullptr) {}

	void insert(const T& data) {
		Node<T>* dataNode = new Node<T>(data);
		if(head == nullptr) {
			head = dataNode;
		} else {
			Node<T>* curr = head;
			while(curr->next) {
				curr = curr->next;
			}
			curr->next = dataNode;
		}
	}

	void print() {
		Node<T>* curr = head;
		while(curr) {
			cout << "|" << curr->data << "| ";
			if(curr->next) {
				cout << "--> ";
			}
			curr = curr->next;
		}
		cout << "--> NULL" << endl;
	}

	~LinkedList() {
		Node<T>* curr = head;
		while(curr) {
			Node<T>* temp = curr;
			curr = curr->next;
			delete temp;
		}
	}
};

int main() {
	LinkedList<string> list;

    list.insert("yo");
    list.insert("20");
    list.insert("bitches");

    std::cout << "Linked List: ";
    list.print();

    return 0;
}
