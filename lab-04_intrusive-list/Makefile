CFLAGS = -Iinclude -Wall -Wextra -Werror -pedantic -std=c17
TARGET = lab-04_intrusive-list

all: $(TARGET)

$(TARGET): obj/clist.elf obj/main.elf 
	gcc $(CFLAGS) -o $(TARGET) obj/clist.elf obj/main.elf 

obj:
	mkdir -p obj

obj/main.elf: src/main.c include/clist.h | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.elf

obj/clist.elf: src/clist.c include/clist.h | obj
	gcc $(CFLAGS) -c src/clist.c -o obj/clist.elf


clean: 
	rm -f obj/main.elf obj/clist.elf
	rm -fr obj
	rm -f $(TARGET)
.PHONY: clean
