CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -Werror -pedantic -g -std=c++17
TARGET = hw-03_mv
TEST_TARGET = test_board

all: $(TARGET)

$(TARGET): obj/main.o obj/Board.o obj/StdioBoardView.o obj/GameController.o 
	$(CXX) $(CXXFLAGS) -o $(TARGET) obj/main.o obj/Board.o obj/StdioBoardView.o obj/GameController.o

obj:
	mkdir -p obj

obj/main.o: src/main.cpp include/Board.h include/StdioBoardView.h include/GameController.h | obj
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

obj/Board.o: src/Board.cpp include/Board.h | obj
	$(CXX) $(CXXFLAGS) -c src/Board.cpp -o obj/Board.o

obj/StdioBoardView.o: src/StdioBoardView.cpp include/StdioBoardView.h | obj
	$(CXX) $(CXXFLAGS) -c src/StdioBoardView.cpp -o obj/StdioBoardView.o

obj/GameController.o: src/GameController.cpp include/GameController.h | obj
	$(CXX) $(CXXFLAGS) -c src/GameController.cpp -o obj/GameController.o

clean: 
	rm -f obj/main.o obj/Board.o obj/StdioBoardView.o obj/GameController.o obj/BoardTest.o obj/Test.o obj/main_test.o
	rm -fr obj
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: clean

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): obj/BoardTest.o obj/Board.o obj/Test.o obj/main_test.o
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) obj/BoardTest.o obj/Board.o obj/Test.o obj/main_test.o

obj/BoardTest.o: test/BoardTest.cpp include/BoardTest.h include/Tests.h include/Board.h | obj
	$(CXX) $(CXXFLAGS) -c test/BoardTest.cpp -o obj/BoardTest.o

obj/Test.o: test/test.cpp include/Tests.h | obj
	$(CXX) $(CXXFLAGS) -c test/Test.cpp -o obj/Test.o

obj/main_test.o: src/main_test.cpp include/BoardTest.h include/Tests.h | obj
	$(CXX) $(CXXFLAGS) -c src/main_test.cpp -o obj/main_test.o
