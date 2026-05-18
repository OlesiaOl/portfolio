CFLAGS = g++ -Iinclude -Wall -Wextra -Werror -pedantic -g -std=c++17
TARGET = task

all: $(TARGET)

$(TARGET): obj/main.elf obj/Resources.elf obj/Room.elf obj/Dungeon.elf obj/BotState.elf obj/ActionWriter.elf obj/BasicBotStrategy.elf obj/InputParser.elf
	$(CFLAGS) -o $(TARGET) obj/main.elf obj/Resources.elf obj/Room.elf obj/Dungeon.elf obj/BotState.elf obj/ActionWriter.elf obj/BasicBotStrategy.elf obj/InputParser.elf

obj:
	mkdir -p obj

obj/main.elf: src/main.cpp include/Resources.h include/Room.h include/Dungeon.h include/BotState.h include/ActionWriter.h include/BasicBotStrategy.h include/InputParser.h | obj
	$(CFLAGS) -c src/main.cpp -o obj/main.elf

obj/Resources.elf: src/Resources.cpp include/Resources.h | obj
	$(CFLAGS) -c src/Resources.cpp -o obj/Resources.elf

obj/Room.elf: src/Room.cpp include/Room.h include/Resources.h | obj
	$(CFLAGS) -c src/Room.cpp -o obj/Room.elf

obj/Dungeon.elf: src/Dungeon.cpp include/Dungeon.h include/Room.h include/Resources.h | obj
	$(CFLAGS) -c src/Dungeon.cpp -o obj/Dungeon.elf

obj/BotState.elf: src/BotState.cpp include/BotState.h include/Resources.h | obj
	$(CFLAGS) -c src/BotState.cpp -o obj/BotState.elf

obj/ActionWriter.elf: src/ActionWriter.cpp include/ActionWriter.h include/Room.h include/BotState.h include/Resources.h | obj
	$(CFLAGS) -c src/ActionWriter.cpp -o obj/ActionWriter.elf

obj/BasicBotStrategy.elf: src/BasicBotStrategy.cpp include/BasicBotStrategy.h include/Dungeon.h include/BotState.h include/ActionWriter.h include/Resources.h | obj
	$(CFLAGS) -c src/BasicBotStrategy.cpp -o obj/BasicBotStrategy.elf

obj/InputParser.elf: src/InputParser.cpp include/InputParser.h include/Dungeon.h include/Resources.h include/Room.h | obj
	$(CFLAGS) -c src/InputParser.cpp -o obj/InputParser.elf

clean:
	rm -f obj/main.elf obj/Resources.elf obj/Room.elf obj/Dungeon.elf obj/BotState.elf obj/ActionWriter.elf obj/BasicBotStrategy.elf obj/InputParser.elf
	rm -fr obj
	rm -f $(TARGET)

.PHONY: clean all