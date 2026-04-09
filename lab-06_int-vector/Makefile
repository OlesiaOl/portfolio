CFLAGS = -Iinclude -Wall -Wextra -Werror -pedantic -std=c++17
TARGET = lab-06_int-vector

$(TARGET): obj/my_vector.elf obj/main.elf 
	g++ $(CFLAGS) -o $(TARGET) obj/my_vector.elf obj/main.elf 

obj: 
	mkdir -p obj

obj/main.elf: src/main.cpp | obj
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.elf

obj/my_vector.elf: src/my_vector.cpp | obj
	g++ $(CFLAGS) -c src/my_vector.cpp -o obj/my_vector.elf 

clean: 
	rm -f obj/my_vector.elf obj/main.elf 
	rm -fr obj
	rm -f $(TARGET)
.PHONY: clean
