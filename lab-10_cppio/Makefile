CFLAGS = g++ -Iinclude -Wall -Wextra -Werror -pedantic -g -std=c++17
TARGET = lab-10_cppio

all: $(TARGET)

$(TARGET): obj/employees.elf obj/bin_manip.elf obj/main.elf 
	$(CFLAGS) -o $(TARGET) obj/employees.elf obj/bin_manip.elf obj/main.elf

obj:
	mkdir -p obj

obj/main.elf: src/main.cpp include/employees.h include/bin_manip.h| obj
	$(CFLAGS) -c src/main.cpp -o obj/main.elf

obj/employees.elf: src/employees.cpp include/employees.h | obj
	$(CFLAGS) -c src/employees.cpp -o obj/employees.elf

obj/bin_manip.elf: src/bin_manip.cpp include/bin_manip.h | obj
	$(CFLAGS) -c src/bin_manip.cpp -o obj/bin_manip.elf

clean: 
	rm -f obj/employees.elf obj/bin_manip.elf obj/main.elf
	rm -fr obj
	rm -f $(TARGET)
.PHONY: clean
