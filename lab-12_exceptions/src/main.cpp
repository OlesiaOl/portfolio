#include <vector>
#include <iostream>

#include <fstream> 
#include <sstream>

#include "matrix.h"

enum class RegisterLimits {
    MinIndex = 0,
    MaxIndex = 9
};

int parse_register(const std::string& reg_str) {
    if (reg_str.empty() || reg_str[0] != '$') {
        throw math::MatrixException("Invalid register format.");
    }
    int index = std::stoi(reg_str.substr(1));
    if (index < static_cast<int>(RegisterLimits::MinIndex) || 
        index > static_cast<int>(RegisterLimits::MaxIndex)) {
        throw math::MatrixException("Invalid register index.");
    }
    return index;
}

int main() {
    math::Matrix registers[10];
    std::string command;

    while (std::getline(std::cin, command)) {
        std::istringstream stream(command);
        std::string cmd;
        stream >> cmd;

        try {
            if (cmd == "print") {
                std::string reg_str;
                stream >> reg_str;
                int index = parse_register(reg_str);
                std::cout << registers[index];
            } else if (cmd == "add") {
                std::string reg1_str, reg2_str;
                stream >> reg1_str >> reg2_str;
                int reg1 = parse_register(reg1_str);
                int reg2 = parse_register(reg2_str);
                registers[reg1] += registers[reg2];
            } else if (cmd == "mul") {
                std::string reg1_str, reg2_str;
                stream >> reg1_str >> reg2_str;
                int reg1 = parse_register(reg1_str);
                int reg2 = parse_register(reg2_str);
                registers[reg1] *= registers[reg2];
            } else if (cmd == "elem") {
                std::string reg_str;
                std::size_t row, column;
                stream >> reg_str >> row >> column;
                int index = parse_register(reg_str);
                std::cout << registers[index].get(row, column) << "\n";
            } else if (cmd == "exit") {
                break;
            } else if (cmd == "load") {
                std::string reg_str, filename;
                stream >> reg_str >> filename;
                int index = parse_register(reg_str);
                std::ifstream file(filename);
                if (!file) {
                    throw math::MatrixException("LOAD: unable to open file.");
                }
                file >> registers[index];
            } else {
                throw math::MatrixException("Unknown command.");
            }
        } catch (const math::MatrixException& e) {
            std::cout << e.what() << "\n";
        } catch (const std::bad_alloc&) {
            std::cout << "Unable to allocate memory.\n";
        } catch (const std::exception& e) {}
    }
    return 0;
}
