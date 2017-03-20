/*
	practice implementation of LinkedList by dha8
	-insert
	-remove
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class T>
struct node { //also could make this a class(where members are private by default), and #include in LinkedList class.
	T value;
	node<T> * next;
};

template<class T>
class LinkedList {
	public:
		LinkedList();
		LinkedList(const LinkedList<T> & rhs);
		LinkedList<T> & operator=(const LinkedList<T> & rhs);
		~LinkedList();

		void append(const T & value);
		void remove(const T & value);
		void traverse();
	private:
		size_t size;
		node<T> * head;
};

//definition
	template<class T>
	LinkedList<T>::LinkedList() : size(0), head(NULL){
	}

	template<class T>
	LinkedList<T>::LinkedList(const LinkedList<T> & rhs){
		head = new node<T>();
		node<T> * curr = rhs.head;
		head->value = curr->value;
		while (curr != NULL) {
			append(curr->value);
			curr = curr->next;
		}
		size = rhs->size;
	}

	template<class T>
	LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> & rhs) {
		if (*this == rhs) return; // check for self-assignment
		delete this; 
		head = new node<T>();
		node<T> * curr = rhs.head;
		head->value = curr->value;
		while (curr != NULL) {
			append(curr->value);
			curr = curr->next;
		}
		size = rhs->size;
	}

	template<class T>
	LinkedList<T>::~LinkedList() {
		if (head == NULL) return;
		node<T> * curr = head;
		while (curr->next != NULL) {
			delete curr->next;
			delete curr;
		}
	}

	template<class T>
	void LinkedList<T>::append(const T & value) {
		if (head == NULL) { // case of inserting the first node
			head = new node<T>;
			head->value = value;
			head->next = NULL;
			size++;
			return;
		}
		node<T> * curr = head;
		while (curr->next != NULL) curr = curr->next; // move to the end of the list
		curr->next = new node<T>; 
		curr->next->value = value; 
		curr->next->next = NULL;
		size++;
	}

	template<class T>
	void LinkedList<T>::remove(const T & value) {
		if (head == NULL) return;
		//remove @ head
		if (head->value == value) {
			node<T> * temp = head->next;
			delete head;
			head = temp;
			return;
		}
		node<T> * curr = head;
		while (curr->next != NULL) {
			if (curr->next->value == value) {
				node<T> * temp = curr->next;
				curr->next = temp->next;
				delete temp;
				return;
			}
			curr = curr->next;
		}
		//removal @ the tail
		if (curr->next->value = value) {
			delete curr->next;
			curr->next = NULL;
		}
	}
	
	template<class T>
	void LinkedList<T>::traverse() {
		if (head == NULL) {
			std::cout << "List is empty!\n";
			return;
		}
		node<T> * curr = head;
		while (curr != NULL) {
			std::cout << curr->value << " ";
			curr = curr->next;
		}
		std::cout << endl;
	}
#endif