#include <my_array.h>
#include <iostream>
using namespace std;
int main() {
	my_array<bool, 10> a;
	a.fill(1);
	a[5] = a[0] = 0;
	for(int i = 0; i < 10; i++)
		cout << a[i] << ' ';
	cout << a.at(9);
	cout << a[10];
	//cout << a.at(10);
}