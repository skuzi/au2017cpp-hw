#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <fstream>
enum Type{DEV=1, SALES=2}; 

class Employee {
public:
  Employee(const char *name, int32_t salary, Type);
  virtual ~Employee();
  Employee(Type);
  Type type() const;
  virtual int salary() const = 0;
protected:
  char _name[255] = {0};
  int32_t _base_salary;
  Type _type;
};

class Developer: public Employee {
public:
  Developer(const char *name, int32_t salary, bool bonus);
  
  Developer();
  ~Developer();
  
  int salary() const;

  friend std::ofstream& operator<<(std::ofstream &os, const Developer &s);
  friend std::ifstream& operator>>(std::ifstream &is, Developer &s);
  friend std::ostream& operator<<(std::ostream &os, const Developer &s);
  friend std::istream& operator>>(std::istream &is, Developer &s);
  
private:
  bool _has_bonus;
};

class SalesManager: public Employee {
public:
  SalesManager(const char *name, int32_t salary, int32_t number, int32_t price);
  
  SalesManager();
  ~SalesManager();

  int salary() const;

  friend std::ofstream& operator<<(std::ofstream &os, const SalesManager &s);
  friend std::ifstream& operator>>(std::ifstream &is, SalesManager &s);
  friend std::ostream& operator<<(std::ostream &os, const SalesManager &s);
  friend std::istream& operator>>(std::istream &is, SalesManager &s);

private:
  int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
  void add(const Employee *e);
  
  EmployeesArray(int sz = 0, int cp = 1);
  ~EmployeesArray();
  
  int total_salary() const;
  int size() const;
  Employee* operator[](int i) const;
  Employee*& operator[](int i);

private:
  int32_t _sz, _cp;
  Employee **_employees;
};

#endif