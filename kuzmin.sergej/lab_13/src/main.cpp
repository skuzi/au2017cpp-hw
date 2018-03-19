#include <my_array.h>
#include <iostream>
using namespace std;
int main() {
	my_array<bool, 10> a;
	a.fill(1);
	a[0] = a[5] = false;
	//a[0] = false;
	a[4] = a[0];
	for(int i = 0; i < 10; i++)
			cout << a[i] << ' ';
	cout << a.at(9);
	//cout << a[10];
	if(sizeof(my_array<bool, 1>) == 1)
		cout << "NICEA";
	a.at(3) = true;
	//cout << a.at(10);
}