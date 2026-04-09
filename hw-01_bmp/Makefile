CFLAGS = -Iinclude -Wall -Wextra -Werror -pedantic -std=c17
TARGET = hw-01_bmp

$(TARGET): obj/bmp.elf obj/main.elf 
	gcc $(CFLAGS) -o $(TARGET) obj/bmp.elf obj/main.elf 

obj: 
	mkdir -p obj

obj/main.elf: src/main.c | obj
	gcc  $(CFLAGS) -c src/main.c -o obj/main.elf

obj/bmp.elf: src/bmp.c | obj
	gcc $(CFLAGS) -c src/bmp.c -o obj/bmp.elf 

clean: 
	rm -f obj/bmp.elf obj/main.elf 
	rm -fr obj
	rm -f $(TARGET)
.PHONY: clean
