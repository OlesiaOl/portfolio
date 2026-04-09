CFLAGS = g++ -Iinclude -Wall -Wextra -Werror -pedantic -g -std=c++17
TARGET = lab-12_exceptions

all: $(TARGET)

$(TARGET): obj/main.elf obj/matrix.elf 
	$(CFLAGS) -o $(TARGET) obj/main.elf obj/matrix.elf

obj:
	mkdir -p obj

obj/main.elf: src/main.cpp include/matrix.h | obj
	$(CFLAGS) -c src/main.cpp -o obj/main.elf

obj/matrix.elf: src/matrix.cpp include/matrix.h | obj
	$(CFLAGS) -c src/matrix.cpp -o obj/matrix.elf

clean: 
	rm -f obj/main.elf obj/matrix.elf
	rm -fr obj
	rm -f $(TARGET)

.PHONY: clean all
