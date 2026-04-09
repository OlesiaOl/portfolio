CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -Werror -pedantic -g -std=c++17

TARGET = hw-02_huffman
TEST_TARGET = test_huffman

all: $(TARGET)

$(TARGET): obj/main.o obj/huffman_tree.o obj/huffman_archiver.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) obj/main.o obj/huffman_tree.o obj/huffman_archiver.o

obj:
	mkdir -p obj

obj/main.o: src/main.cpp include/huffman_tree.hpp include/huffman_archiver.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

obj/huffman_tree.o: src/huffman_tree.cpp include/huffman_tree.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/huffman_tree.cpp -o obj/huffman_tree.o

obj/huffman_archiver.o: src/huffman_archiver.cpp include/huffman_archiver.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/huffman_archiver.cpp -o obj/huffman_archiver.o


test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): obj/huffman_archiver_test.o obj/huffman_tree.o obj/huffman_archiver.o obj/my_tests.o obj/main_test.o
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) obj/huffman_archiver_test.o obj/huffman_tree.o obj/huffman_archiver.o obj/my_tests.o obj/main_test.o

obj/huffman_archiver_test.o: my_tests/huffman_archiver_test.cpp include/huffman_archiver_test.hpp include/huffman_archiver.hpp include/my_tests.hpp | obj
	$(CXX) $(CXXFLAGS) -c my_tests/huffman_archiver_test.cpp -o obj/huffman_archiver_test.o

obj/my_tests.o: my_tests/my_tests.cpp include/my_tests.hpp | obj
	$(CXX) $(CXXFLAGS) -c my_tests/my_tests.cpp -o obj/my_tests.o

obj/main_test.o: src/main_test.cpp include/huffman_archiver_test.hpp include/my_tests.hpp | obj
	$(CXX) $(CXXFLAGS) -c src/main_test.cpp -o obj/main_test.o


clean:
	rm -f obj/main.o
	rm -f obj/huffman_tree.o
	rm -f obj/huffman_archiver.o
	rm -f obj/huffman_archiver_test.o
	rm -f obj/my_tests.o
	rm -f obj/main_test.o
	rm -fr obj
	rm -f $(TARGET)
	rm -f $(TEST_TARGET)

.PHONY: clean test all
