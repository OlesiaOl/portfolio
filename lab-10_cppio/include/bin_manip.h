#ifndef BIN_MANIP
#define BIN_MANIP

#include <iostream>
#include <cstdint>
#include <cstring>
#include <fstream>

struct write_le_int32 {
    std::int32_t val;
    explicit write_le_int32(std::int32_t value_) : val(value_) {}
};

struct read_le_int32 {
    std::int32_t val;
    read_le_int32(std::int32_t value = 0) : val(value) {}
};


struct write_bool {
    int val;
    explicit write_bool(bool value) : val(value) {}
};

struct read_bool {
    int val;
    read_bool(bool value = false) : val(value) {}
};

struct write_str {
    const char* val;
    explicit write_str(const char* value) : val(value) {}
};

struct read_str {
    char* buffer;
    size_t max_size;
};

std::ofstream& operator<<(std::ofstream& os, write_le_int32 cur);
std::ifstream& operator>>(std::ifstream& is, read_le_int32& cur);

std::ofstream& operator<<(std::ofstream& os, write_bool cur);
std::ifstream& operator>>(std::ifstream& is, read_bool& cur);

std::ofstream& operator<<(std::ofstream& os, write_str cur);
std::ifstream& operator>>(std::ifstream& is, read_str& cur);

#endif // BIN_MANIP
