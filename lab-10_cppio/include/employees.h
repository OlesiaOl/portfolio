#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED
/*
#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

class Employee {
protected:
  char* _name;
  int32_t _base_salary;

public:
  Employee(const char* name = "", int32_t base_salary = 0);
  virtual ~Employee();

  void copyName(const char *name);

  virtual int salary() const = 0;

  virtual void print(std::ostream &os) const = 0;
  virtual void print_bin(std::ofstream &os) const = 0;
  virtual void read_bin(std::ifstream &is) = 0;
};


class Developer final: public Employee {
public:
  Developer(const char* name = "", int32_t base_salary = 0, bool has_bonus = false);
  Developer(const Developer& other);
  ~Developer() {};
  Developer& operator=(const Developer &other); 

  int salary() const override {
    int salary = _base_salary;
    return salary;
  }

  void print(std::ostream &os) const override;
  void print_bin(std::ofstream &os) const override;
  void read_bin(std::ifstream &is) override;

  friend std::istream& operator>>(std::istream& is, Developer& developer);
  friend std::ostream& operator<<(std::ostream &os, const Developer& d);

private:
    bool _has_bonus;
};


class SalesManager final: public Employee {
public:
  SalesManager(const char* name = "", int32_t base_salary = 0, int32_t sold_nm = 0, int32_t price = 0);
  SalesManager(const SalesManager& other);
  SalesManager& operator=(const SalesManager& other);
  ~SalesManager() {};

  int salary() const override {
    return _base_salary + _sold_nm * _price * 0.01;
  }

  void print(std::ostream &os) const override;
  void print_bin(std::ofstream &os) const override;
  void read_bin(std::ifstream &is) override;

  friend std::ostream& operator<<(std::ostream& os, const SalesManager& m);
  friend std::istream& operator>>(std::istream& in, SalesManager& manager);

private:
  int32_t _sold_nm, _price;
};


class EmployeesArray {
public:
  EmployeesArray();
  ~EmployeesArray();
  void add(Employee *e);
  int total_salary() const;

  size_t get_count() const;
  Employee* get_employee(size_t index);

  void print(std::ostream &os) const;
  void print_bin(std::ofstream &os) const;
  void read_bin(std::ifstream &is);

  friend std::ostream& operator<<(std::ostream &os, const EmployeesArray &array);
  friend std::istream& operator>>(std::istream &in, EmployeesArray &array);

private:
  std::vector<Employee*> _employees;
};

Employee* create_employee_by_marker(int32_t marker);


#endif
*/


#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

class Employee {
protected:
  char* _name;  
  int32_t _base_salary;

public:
  Employee(const char* name = "", int32_t base_salary = 0);
  virtual ~Employee();

  void copyName(const char *name);

  virtual int salary() const = 0;

  virtual void print(std::ostream &os) const = 0;
  virtual void print_bin(std::ofstream &os) const = 0;
  virtual void read_bin(std::ifstream &is) = 0;
};


class Developer final: public Employee {
public:
  Developer(const char* name = "", int32_t base_salary = 0, bool has_bonus = false);
  Developer(const Developer& other);
  ~Developer() {};
  Developer& operator=(const Developer &other); 

  int salary() const override {
    int salary = _base_salary;
    return salary;
  }

  void print(std::ostream &os) const override;
  void print_bin(std::ofstream &os) const override;
  void read_bin(std::ifstream &is) override;

  friend std::istream& operator>>(std::istream& is, Developer& developer);
  friend std::ostream& operator<<(std::ostream &os, const Developer& d);

private:
    bool _has_bonus;
};


class SalesManager final: public Employee {
public:
  SalesManager(const char* name = "", int32_t base_salary = 0, int32_t sold_nm = 0, int32_t price = 0);
  SalesManager(const SalesManager& other);
  SalesManager& operator=(const SalesManager& other);
  ~SalesManager() {};

  int salary() const override {
    return _base_salary + _sold_nm * _price * 0.01;
  }

  void print(std::ostream &os) const override;
  void print_bin(std::ofstream &os) const override;
  void read_bin(std::ifstream &is) override;

  friend std::ostream& operator<<(std::ostream& os, const SalesManager& m);
  friend std::istream& operator>>(std::istream& in, SalesManager& manager);

private:
  int32_t _sold_nm, _price;
};


class EmployeesArray {
public:
  EmployeesArray();
  ~EmployeesArray();
  void add(Employee *e);
  int total_salary() const;

  size_t get_count() const;
  Employee* get_employee(size_t index);

  void print(std::ostream &os) const;
  void print_bin(std::ofstream &os) const;
  void read_bin(std::ifstream &is);

  friend std::ostream& operator<<(std::ostream &os, const EmployeesArray &array);
  friend std::istream& operator>>(std::istream &in, EmployeesArray &array);

private:
  std::vector<Employee*> _employees;
};

Employee* create_employee_by_marker(int32_t marker);


#endif 
