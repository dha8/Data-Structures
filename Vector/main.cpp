#include <iostream>
#include <Vector.h> // wtf?
using namespace std;

int main() {
	cout << "hello world!" << endl;
	Vector<int> * v_ptr = new Vector<int>();
	Vector<int> v_stack;
	cout << "v_heap has a size of " << v_ptr->getSize() << endl;
	cout << "v_stack has a size of " << v_stack.getSize() << endl;
	v_ptr->append(1);
	v_ptr->append(2);
	v_ptr->append(3);

	v_stack.append(4);
	v_stack.append(5);
	v_stack.append(6);

	for (unsigned int i = 0; i < v_ptr->getSize(); ++i) {
		cout << (*v_ptr)[i] << " "; 
	}
	cout << endl;
	for (unsigned int i = 0; i < v_stack.getSize(); ++i) {
		cout << v_stack[i] << " ";
	}
}