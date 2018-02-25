#include "employees.h"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

int main() {
	EmployeesArray arr;
	std::string cmd;
	while(1) {
		cin >> cmd;
		
		if(cmd == "list"){
			for(int i = 0; i < arr.size(); i++) {
				cout << i + 1 << ". ";
				
				if(arr[i]->type() == DEV)
					cout << *((Developer*)arr[i]);

				if(arr[i]->type() == SALES)
					cout << *((SalesManager*)arr[i]);
			}
			cout << "== Total salary: " << arr.total_salary() << "\n\n";
		}
		else if(cmd == "load") {
			char fname[255];
			cin >> fname;
			std::ifstream is(fname, std::ifstream::binary);

			while(1) {
				int32_t t;
				is.read((char*)&t, sizeof(int32_t));
				if(is.eof() || (t != 1 && t != 2)) 
					break;

				if(t == 1) {
					Developer* d = new Developer();
					is >> *d;
					arr.add(d);
				}

				if(t == 2) {
					SalesManager* s = new SalesManager();
					is >> *s;
					arr.add(s);
				}
			}
		}
		else if(cmd == "add") {
			int32_t t;
			cin >> t;

			if(t == 1) {
				Developer* d = new Developer();
				cin >> *d;
				arr.add(d);
			}

			if(t == 2) {
				SalesManager* s = new SalesManager();
				cin >> *s;
				arr.add(s);
			}
		}
		else if(cmd == "save") {
			char fname[255];
			cin >> fname;
			std::ofstream os(fname, std::ofstream::binary);

			for(int i = 0; i < arr.size(); i++) {
				if(arr[i]->type() == DEV)
					os << *((Developer*)arr[i]);
				
				if(arr[i]->type() == SALES)
					os << *((SalesManager*)arr[i]);
			}
		}
		else if(cmd == "exit"){
			break;
		}
	}
}