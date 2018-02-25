#include "employees.h"
#include <cstring>

int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}

int Developer::salary() const {
	return _base_salary + _has_bonus * 1000;
}

Employee::Employee(const char *name, int32_t salary, Type t):
	_base_salary(salary), _type(t) 
{
	strncpy(_name, name, strlen(name));
}

Employee::~Employee() {}

Developer::Developer(const char *name, int32_t salary, bool bonus):
	Employee(name, salary, DEV), _has_bonus(bonus) {}

SalesManager::SalesManager(const char *name, int32_t salary, int32_t number, int32_t price):
	Employee(name, salary, SALES), _sold_nm(number), _price(price) {}

int EmployeesArray::total_salary() const {
	int total = 0;
	for (int i = 0; i < _sz; i++) {
		total += _employees[i]->salary();
	}
	return total;
}

void EmployeesArray::add(const Employee *e) {
	if(_sz == _cp) {
		Employee **tmp = new Employee* [_cp = 2 * _sz];
		memcpy(tmp, _employees, _sz * sizeof(Employee*));
		delete [] _employees;
		_employees = tmp;
	}
	_employees[_sz++] = (Employee*)e;
}

EmployeesArray::EmployeesArray(int sz, int cp):
	_sz(sz), _cp(cp), _employees(new Employee*[_cp]) {}

EmployeesArray::~EmployeesArray() {
	for(int i = 0; i < _sz; i++)
		delete _employees[i];
	delete [] _employees;
}

int EmployeesArray::size() const {
	return _sz;
}

std::ofstream& operator<<(std::ofstream &os, const SalesManager &s) {
	os.write((char*)&s._type, sizeof(int32_t));
	os.write(s._name, (strlen(s._name) + 1) * sizeof(char));
	os.write((char*)&s._base_salary, sizeof(int32_t));
	os.write((char*)&s._sold_nm, sizeof(int32_t));
	os.write((char*)&s._price, sizeof(int32_t));
	return os;
}

std::ifstream& operator>>(std::ifstream &is, SalesManager &s) {
	for(int i = 0; i < 255; i++) {
		is.read(s._name + i, sizeof(char));
		if(!s._name[i])
			break;
	}
	is.read((char*)&s._base_salary, sizeof(int32_t));
	is.read((char*)&s._sold_nm, sizeof(int32_t));
	is.read((char*)&s._price, sizeof(int32_t));
	return is;
}

std::ostream& operator<<(std::ostream &os, const SalesManager &s) {
	os << "Sales Manager\n";
	os << "Name: " << s._name << '\n';
	os << "Base Salary: " << s._base_salary << '\n';
	os << "Sold items: " << s._sold_nm << '\n';
	os << "Item price: " << s._price << '\n';
	return os;
}

std::istream& operator>>(std::istream &is, SalesManager &s) {
	is >> s._name >> s._base_salary >> s._sold_nm >> s._price;
	return is;
}

std::ofstream& operator<<(std::ofstream &os, const Developer &s) {
	os.write((char*)&s._type, sizeof(int32_t));
	os.write(s._name, (strlen(s._name) + 1) * sizeof(char));
	os.write((char*)&s._base_salary, sizeof(int32_t));
	os.write((char*)&s._has_bonus, sizeof(bool));
	return os;
}

std::ifstream& operator>>(std::ifstream &is, Developer &s) {
	for(int i = 0; i < 255; i++) {
		is.read(s._name + i, sizeof(char));
		if(!s._name[i])
			break;
	}
	is.read((char*)&s._base_salary, sizeof(int32_t));
	is.read((char*)&s._has_bonus, sizeof(bool));
	return is;
}

std::ostream& operator<<(std::ostream &os, const Developer &s) {
	os << "Developer\n";
	os << "Name: " << s._name << '\n';
	os << "Base Salary: " << s._base_salary << '\n';
	os << "Has bonus: " << (s._has_bonus ? '+' : '-') << '\n';
	return os;
}

std::istream& operator>>(std::istream &is, Developer &s) {
	is >> s._name >> s._base_salary >> s._has_bonus;
	return is;
}

Employee* EmployeesArray::operator[](int i) const {
	return _employees[i];
}

Employee*& EmployeesArray::operator[](int i) {
	return _employees[i];
}

Type Employee::type() const {
	return _type;
}

Developer::Developer():
	Employee(DEV) {}

SalesManager::SalesManager():
	Employee(SALES) {}

Employee::Employee(Type t):
	_type(t) {}

Developer::~Developer() {}

SalesManager::~SalesManager() {}