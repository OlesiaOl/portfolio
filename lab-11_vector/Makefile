CFLAGS = g++ -Iinclude -Wall -Wextra -Werror -pedantic -g -std=c++17
TARGET = lab-11_vector

all: $(TARGET)

$(TARGET): obj/main.elf 
	$(CFLAGS) -o $(TARGET) obj/main.elf

obj:
	mkdir -p obj

obj/main.elf: src/main.cpp include/my_vector_impl.hpp include/my_vector.hpp| obj
	$(CFLAGS) -c src/main.cpp -o obj/main.elf

clean: 
	rm -f obj/main.elf
	rm -fr obj
	rm -f $(TARGET)
.PHONY: clean
