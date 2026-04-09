#include "bin_manip.h"
#include <cstring>
#include <fstream>

std::ofstream& operator<<(std::ofstream& os, write_le_int32 cur) {
    char bytes[4];
    std::memcpy(bytes, &cur.val, 4);
    os.write(bytes, 4);
    return os;
}

std::ifstream& operator>>(std::ifstream& is, read_le_int32& cur) {
    char bytes[4];
    if (is.read(bytes, 4)) {
        cur.val = static_cast<std::uint32_t>(static_cast<unsigned char>(bytes[0])) | 
                  (static_cast<std::uint32_t>(static_cast<unsigned char>(bytes[1])) << 8) | 
                  (static_cast<std::uint32_t>(static_cast<unsigned char>(bytes[2])) << 16) | 
                  (static_cast<std::uint32_t>(static_cast<unsigned char>(bytes[3])) << 24);
    }
    return is;
}


std::ofstream& operator<<(std::ofstream& os, write_bool cur) {
    os.put(cur.val ? 1 : 0);
    return os;
}

std::ifstream& operator>>(std::ifstream& is, read_bool& cur) {
    char byte;
    if (is.read(&byte, 1)) {
        cur.val = (byte != 0);
    }
    return is;
}


std::ofstream& operator<<(std::ofstream& os, write_str cur) {
    size_t len = std::strlen(cur.val);
    os.write(cur.val, len);
    os.put('\0');
    return os;
}

std::ifstream& operator>>(std::ifstream& is, read_str& cur) {
    char* buff = cur.buffer;
    size_t max_size = cur.max_size;
    size_t current_size = 0;
    while (current_size < max_size) {
        char ch;
        if (!is.get(ch)) {
            break;
        }
        buff[current_size++] = ch;
        if (ch == '\0') {
            break;
        }
    }
    return is;
}
