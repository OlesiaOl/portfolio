/*#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

#include "bin_manip.h"
#include "employees.h"


Employee::Employee(const char *name, int32_t base_salary) : _base_salary(base_salary) {
    _name = new char[std::strlen(name) + 1];
    std::strcpy(_name, name);
}

Employee::~Employee() {
    delete[] _name;
}

void Employee::copyName(const char *name) {
    delete[] _name;
    _name = new char[std::strlen(name) + 1];
    std::strcpy(_name, name);
}

Employee* create_employee_by_marker(int32_t marker) {
    if (marker == 1) {
        return new Developer();
    } else if (marker == 2) {
        return new SalesManager();
    } else {
        return nullptr;
    }
}

Developer::Developer(const char* name, int32_t base_salary, bool has_bonus)
    : Employee(name, base_salary), _has_bonus(has_bonus) {}


Developer::Developer(const Developer& other)
    : Employee(other._name, other._base_salary), _has_bonus(other._has_bonus) {
    _name = new char[std::strlen(other._name) + 1];
    std::strcpy(_name, other._name);
}

Developer& Developer::operator=(const Developer &other) {
    if (this == &other) {
        return *this;
    }
    copyName(other._name);
    _base_salary = other._base_salary;
    _has_bonus = other._has_bonus;
    return *this;
}


void Developer::print(std::ostream& os) const {
    os << "Developer\n" 
       << "Name: " << _name << "\n"
       << "Base Salary: " << _base_salary << "\n"
       << "Has bonus: " << (_has_bonus ? "+" : "-") << "\n";
}

void Developer::print_bin(std::ofstream &os) const {
    int32_t marker = 1;
    os.write(reinterpret_cast<const char*>(&marker), sizeof(marker));
    os << write_str(_name)
       << write_le_int32(_base_salary)
       << write_bool(_has_bonus);
}

void Developer::read_bin(std::ifstream &is) {
    char nameBuffer[256] = {0};
    read_str nameRs { nameBuffer, sizeof(nameBuffer) };
    is >> nameRs;
    copyName(nameBuffer);

    read_le_int32 baseSalary;
    is >> baseSalary;
    _base_salary = baseSalary.val;

    read_bool hasBonus;
    is >> hasBonus;
    _has_bonus = hasBonus.val;
}

std::istream& operator>>(std::istream& is, Developer& developer) {
    std::string name;
    is >> name >> developer._base_salary >> developer._has_bonus;
    developer.copyName(name.c_str());
    return is;
}

std::ostream& operator<<(std::ostream &os, const Developer& d) {
    os << "Developer\n"
       << "Name: " << d._name << "\n"
       << "Base Salary: " << d._base_salary << "\n"
       << "Has bonus: " << (d._has_bonus ? "+" : "-") << "\n";
    return os;
}

SalesManager::SalesManager(const char* name, int32_t base_salary, int32_t sold_nm, int32_t price)
    : Employee(name, base_salary), _sold_nm(sold_nm), _price(price) {}

SalesManager::SalesManager(const SalesManager& other)
    : Employee(other._name, other._base_salary), _sold_nm(other._sold_nm), _price(other._price) {
    _name = new char[std::strlen(other._name) + 1];
    std::strcpy(_name, other._name);
}


SalesManager& SalesManager::operator=(const SalesManager& other) {
    if (this == &other) {
        return *this;
    }
    copyName(other._name);
    _base_salary = other._base_salary;
    _sold_nm = other._sold_nm;
    _price = other._price;
    return *this;
}


void SalesManager::print(std::ostream &os) const {
    os << "Sales Manager\n" 
       << "Name: " << _name << "\n"
       << "Base Salary: " << _base_salary << "\n"
       << "Sold items: " << _sold_nm << "\n"
       << "Item price: " << _price << "\n";
}

void SalesManager::print_bin(std::ofstream &os) const {
    int32_t marker = 2;
    os.write(reinterpret_cast<const char*>(&marker), sizeof(marker));
    os << write_str(_name)
       << write_le_int32(_base_salary)
       << write_le_int32(_sold_nm)
       << write_le_int32(_price);
}

void SalesManager::read_bin(std::ifstream &is) {
    char nameBuffer[256] = {0};
    read_str nameRs { nameBuffer, sizeof(nameBuffer) };
    is >> nameRs;
    copyName(nameBuffer);

    read_le_int32 base_salary, sold_nm, price;
    is >> base_salary >> sold_nm >> price;

    _base_salary = base_salary.val;
    _sold_nm = sold_nm.val;
    _price = price.val;
}


std::istream& operator>>(std::istream& in, SalesManager& manager) {
    std::string name;
    in >> name >> manager._base_salary >> manager._sold_nm >> manager._price;
    manager.copyName(name.c_str());
    return in;
}

std::ostream& operator<<(std::ostream& os, const SalesManager& m) {
    os << "Sales Manager\n" 
       << "Name: " << m._name << "\n"
       << "Base Salary: " << m._base_salary << "\n"
       << "Sold items: " << m._sold_nm << "\n"
       << "Item price: " << m._price << "\n";
    return os;
}

EmployeesArray::EmployeesArray() {}

EmployeesArray::~EmployeesArray() {
    for (auto* employee : _employees) {
        delete employee;
    }
    _employees.clear();
}

void EmployeesArray::add(Employee *e) {
    _employees.push_back(e);
}

int EmployeesArray::total_salary() const {
    int total_sal = 0;
    for (auto* employee : _employees) {
        total_sal += employee->salary();
    }
    return total_sal;
}

size_t EmployeesArray::get_count() const {
    return _employees.size();
}

Employee* EmployeesArray::get_employee(size_t index) {
    if (index < _employees.size()) {
        return _employees[index];
    }
    return nullptr;
}

void EmployeesArray::print(std::ostream &os) const {
    int number = 1;
    for (auto* employee : _employees) {
        os << number << ". ";
        employee->print(os);
        number++;
    }
    os << "== Total salary: " << total_salary() << "\n\n";
}

void EmployeesArray::print_bin(std::ofstream &os) const {
    int32_t count = static_cast<int32_t>(_employees.size());
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& employee : _employees) {
        employee->print_bin(os);
    }
}

void EmployeesArray::read_bin(std::ifstream &is) {
    int32_t count;
    if (!is.read(reinterpret_cast<char*>(&count), sizeof(count))) {
       return;
    }
    for (int32_t i = 0; i < count; ++i) {
        int32_t type;
        if (!is.read(reinterpret_cast<char*>(&type), sizeof(type))) {
           is.setstate(std::ios::failbit);
           return;
         }
        Employee* emp = create_employee_by_marker(type);
        if (emp != nullptr) {
            emp->read_bin(is);
            _employees.push_back(emp);
        } else {
            is.setstate(std::ios::failbit);
            return;
        }
    }
}

std::istream& operator>>(std::istream &in, EmployeesArray &array) {
    std::string command;
    in >> command;
    if (command == "add") {
        std::string type;
        in >> type;
        Employee* emp = nullptr;
        if (type == "Developer") {
            emp = new Developer();
        } else if (type == "SalesManager") {
            emp = new SalesManager();
        } else {
            std::cout << "Invalid employee type: " << type << std::endl;
        }
        if (emp != nullptr) {
            if (type == "Developer") {
                in >> *(static_cast<Developer*>(emp));
            } else if (type == "SalesManager") {
                in >> *(static_cast<SalesManager*>(emp));
            }
            array.add(emp);
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& os, const EmployeesArray &array) {
    array.print(os);
    return os;
}
*/





#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

#include "bin_manip.h"
#include "employees.h"

Employee::Employee(const char *name, int32_t base_salary) : _base_salary(base_salary) {
    _name = new char[std::strlen(name) + 1];
    std::strcpy(_name, name);
}

Employee::~Employee() {
    delete[] _name;
}

void Employee::copyName(const char *name) {
    delete[] _name;
    _name = new char[std::strlen(name) + 1];
    std::strcpy(_name, name);
}


Employee* create_employee_by_marker(int32_t marker) {
    if (marker == 1) {
        return new Developer();
    } else if (marker == 2) {
        return new SalesManager();
    } else {
        return nullptr;
    }
}

Developer::Developer(const char* name, int32_t base_salary, bool has_bonus)
    : Employee(name, base_salary), _has_bonus(has_bonus) {}

Developer::Developer(const Developer& other)
    : Employee(other._name, other._base_salary), _has_bonus(other._has_bonus) {
    _name = new char[std::strlen(other._name) + 1];
    std::strcpy(_name, other._name);
}

Developer& Developer::operator=(const Developer &other) {
    if (this == &other) {
        return *this;
    }
    copyName(other._name);
    _base_salary = other._base_salary;
    _has_bonus = other._has_bonus;
    return *this;
}

void Developer::print(std::ostream& os) const {
    os << "Developer\n" 
       << "Name: " << _name << "\n"
       << "Base Salary: " << _base_salary << "\n"
       << "Has bonus: " << (_has_bonus ? "+" : "-") << "\n";
}

void Developer::print_bin(std::ofstream &os) const {
    int32_t marker = 1;
    os.write(reinterpret_cast<const char*>(&marker), sizeof(marker));
    os << write_str(_name)
       << write_le_int32(_base_salary)
       << write_bool(_has_bonus);
}

void Developer::read_bin(std::ifstream &is) {
    char nameBuffer[256] = {0};
    read_str nameRs { nameBuffer, sizeof(nameBuffer) };
    is >> nameRs;
    copyName(nameBuffer);

    read_le_int32 baseSalary;
    is >> baseSalary;
    _base_salary = baseSalary.val;

    read_bool hasBonus;
    is >> hasBonus;
    _has_bonus = hasBonus.val;
}

std::istream& operator>>(std::istream& is, Developer& developer) {
    std::string name;
    is >> name >> developer._base_salary >> developer._has_bonus;
    developer.copyName(name.c_str());
    return is;
}

std::ostream& operator<<(std::ostream &os, const Developer& d) {
    os << "Developer\n"
       << "Name: " << d._name << "\n"
       << "Base Salary: " << d._base_salary << "\n"
       << "Has bonus: " << (d._has_bonus ? "+" : "-") << "\n";
    return os;
}

SalesManager::SalesManager(const char* name, int32_t base_salary, int32_t sold_nm, int32_t price)
    : Employee(name, base_salary), _sold_nm(sold_nm), _price(price) {}

SalesManager::SalesManager(const SalesManager& other)
    : Employee(other._name, other._base_salary), _sold_nm(other._sold_nm), _price(other._price) {
    _name = new char[std::strlen(other._name) + 1];
    std::strcpy(_name, other._name);
}

SalesManager& SalesManager::operator=(const SalesManager& other) {
    if (this == &other) {
        return *this;
    }
    copyName(other._name);
    _base_salary = other._base_salary;
    _sold_nm = other._sold_nm;
    _price = other._price;
    return *this;
}

void SalesManager::print(std::ostream &os) const {
    os << "Sales Manager\n" 
       << "Name: " << _name << "\n"
       << "Base Salary: " << _base_salary << "\n"
       << "Sold items: " << _sold_nm << "\n"
       << "Item price: " << _price << "\n";
}

void SalesManager::print_bin(std::ofstream &os) const {
    int32_t marker = 2;
    os.write(reinterpret_cast<const char*>(&marker), sizeof(marker));
    os << write_str(_name)
       << write_le_int32(_base_salary)
       << write_le_int32(_sold_nm)
       << write_le_int32(_price);
}

void SalesManager::read_bin(std::ifstream &is) {
    char nameBuffer[256] = {0};
    read_str nameRs { nameBuffer, sizeof(nameBuffer) };
    is >> nameRs;
    copyName(nameBuffer);

    read_le_int32 base_salary, sold_nm, price;
    is >> base_salary >> sold_nm >> price;

    _base_salary = base_salary.val;
    _sold_nm = sold_nm.val;
    _price = price.val;
}

std::istream& operator>>(std::istream& in, SalesManager& manager) {
    std::string name;
    in >> name >> manager._base_salary >> manager._sold_nm >> manager._price;
    manager.copyName(name.c_str());
    return in;
}

std::ostream& operator<<(std::ostream& os, const SalesManager& m) {
    os << "Sales Manager\n" 
       << "Name: " << m._name << "\n"
       << "Base Salary: " << m._base_salary << "\n"
       << "Sold items: " << m._sold_nm << "\n"
       << "Item price: " << m._price << "\n";
    return os;
}

EmployeesArray::EmployeesArray() {}

EmployeesArray::~EmployeesArray() {
    for (auto* employee : _employees) {
        delete employee;
    }
    _employees.clear();
}

void EmployeesArray::add(Employee *e) {
    _employees.push_back(e);
}

int EmployeesArray::total_salary() const {
    int total_sal = 0;
    for (auto* employee : _employees) {
        total_sal += employee->salary();
    }
    return total_sal;
}

size_t EmployeesArray::get_count() const {
    return _employees.size();
}

Employee* EmployeesArray::get_employee(size_t index) {
    if (index < _employees.size()) {
        return _employees[index];
    }
    return nullptr;
}

void EmployeesArray::print(std::ostream &os) const {
    int number = 1;
    for (auto* employee : _employees) {
        os << number << ". ";
        employee->print(os);
        number++;
    }
    os << "== Total salary: " << total_salary() << "\n\n";
}

void EmployeesArray::print_bin(std::ofstream &os) const {
    int32_t count = static_cast<int32_t>(_employees.size());
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& employee : _employees) {
        employee->print_bin(os);
    }
}

void EmployeesArray::read_bin(std::ifstream &is) {
    int32_t count;
    if (!is.read(reinterpret_cast<char*>(&count), sizeof(count))) {
       return;
    }
    for (int32_t i = 0; i < count; ++i) {
        int32_t type;
        if (!is.read(reinterpret_cast<char*>(&type), sizeof(type))) {
           is.setstate(std::ios::failbit);
           return;
         }
        Employee* emp = create_employee_by_marker(type);
        if (emp != nullptr) {
            emp->read_bin(is);
            _employees.push_back(emp);
        } else {
            is.setstate(std::ios::failbit);
            return;
        }
    }
}

std::istream& operator>>(std::istream &in, EmployeesArray &array) {
    std::string command;
    in >> command;
    if (command == "add") {
        std::string type;
        in >> type;
        Employee* emp = nullptr;
        if (type == "Developer") {
            emp = new Developer();
        } else if (type == "SalesManager") {
            emp = new SalesManager();
        } else {
            std::cout << "Invalid employee type: " << type << std::endl;
        }
        if (emp != nullptr) {
            if (type == "Developer") {
                in >> *(static_cast<Developer*>(emp));
            } else if (type == "SalesManager") {
                in >> *(static_cast<SalesManager*>(emp));
            }
            array.add(emp);
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& os, const EmployeesArray &array) {
    array.print(os);
    return os;
}