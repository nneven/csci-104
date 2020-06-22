#include "stack.h"
#include <iostream>
using namespace std;

int main() {
	Stack<int> s;
	s.push(0);
	s.push(1);
	s.push(2);
	cout << s.size() << endl;
	s.pop();
	cout << s.top() << endl;
	s.pop();
	cout << s.size() << endl;
	s.pop();
	if (s.empty()) cout << "EMPTY" << endl;
	return 1;
}