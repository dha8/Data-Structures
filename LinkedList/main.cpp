#include <iostream>
#include <LinkedList.h> // wtf?
using namespace std;

int main() {
	cout << "hello world!" << endl;
	LinkedList<int> * list = new LinkedList<int>();
	list->append(1); 
	list->append(2);
	list->append(3);
	list->traverse();
	list->remove(1);
	list->traverse();
}