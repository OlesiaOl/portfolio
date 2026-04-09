#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

#include "bin_manip.h"
#include "employees.h"

int main() {
    EmployeesArray employees;
    std::string command;

    while (std::cin >> command) {
        if (command == "exit") {
            break;
        } else if (command == "load") {
            std::string filename;
            std::cin >> filename;
            std::ifstream infile(filename, std::ios::binary);
            if (!infile.is_open()) {
                std::cerr << "Ошибка при открытии файла!" << std::endl;
                continue;
            }
            employees.read_bin(infile);
            infile.close();
        } else if (command == "save") {
            std::string filename;
            std::cin >> filename;
            std::ofstream outfile(filename, std::ios::binary);
            if (outfile.is_open()) {
                employees.print_bin(outfile);
                outfile.close();
            } else {
                std::cerr << "Error opening file: " << filename << std::endl;
            }
        } else if (command == "list") {
            std::cout << employees;
        } else if (command == "add") {
            int type;
            std::cin >> type;
            if (type == 1) {
                std::string name;
                int32_t base_salary;
                bool has_bonus;
                std::cin >> name >> base_salary >> has_bonus;
                Developer* developer = new Developer(name.c_str(), base_salary, has_bonus);
                employees.add(developer);
            } else if (type == 2) {
                std::string name;
                int32_t base_salary, sold_items, item_price;
                std::cin >> name >> base_salary >> sold_items >> item_price;
                SalesManager* manager = new SalesManager(name.c_str(), base_salary, sold_items, item_price);
                employees.add(manager);
            } else {
                std::cout << "Unknown employee type: " << type << std::endl;
            }
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
    return 0;
}
