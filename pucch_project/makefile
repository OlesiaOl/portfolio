CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Iinclude

BUILD_DIR = build

APP = $(BUILD_DIR)/app
TEST_APP = $(BUILD_DIR)/tests_app

APP_OBJ = \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/qpsk.o \
	$(BUILD_DIR)/encoder.o \
	$(BUILD_DIR)/decoder.o \
	$(BUILD_DIR)/channel.o \
	$(BUILD_DIR)/simulation.o

TEST_OBJ = \
	$(BUILD_DIR)/test_main.o \
	$(BUILD_DIR)/test_qpsk.o \
	$(BUILD_DIR)/test_encoder.o \
	$(BUILD_DIR)/test_decoder.o \
	$(BUILD_DIR)/test_channel.o \
	$(BUILD_DIR)/test_simulation.o \
	$(BUILD_DIR)/qpsk.o \
	$(BUILD_DIR)/encoder.o \
	$(BUILD_DIR)/decoder.o \
	$(BUILD_DIR)/channel.o \
	$(BUILD_DIR)/simulation.o

all: $(APP)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: src/main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/qpsk.o: src/qpsk.cpp include/qpsk.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/qpsk.cpp -o $(BUILD_DIR)/qpsk.o

$(BUILD_DIR)/encoder.o: src/encoder.cpp include/encoder.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/encoder.cpp -o $(BUILD_DIR)/encoder.o

$(BUILD_DIR)/decoder.o: src/decoder.cpp include/decoder.h include/encoder.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/decoder.cpp -o $(BUILD_DIR)/decoder.o

$(BUILD_DIR)/channel.o: src/channel.cpp include/channel.h include/qpsk.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/channel.cpp -o $(BUILD_DIR)/channel.o

$(BUILD_DIR)/simulation.o: src/simulation.cpp include/simulation.h include/encoder.h include/decoder.h include/qpsk.h include/channel.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c src/simulation.cpp -o $(BUILD_DIR)/simulation.o

$(BUILD_DIR)/test_main.o: tests/test_main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c tests/test_main.cpp -o $(BUILD_DIR)/test_main.o

$(BUILD_DIR)/test_qpsk.o: tests/test_qpsk.cpp include/qpsk.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c tests/test_qpsk.cpp -o $(BUILD_DIR)/test_qpsk.o

$(BUILD_DIR)/test_encoder.o: tests/test_encoder.cpp include/encoder.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c tests/test_encoder.cpp -o $(BUILD_DIR)/test_encoder.o

$(BUILD_DIR)/test_decoder.o: tests/test_decoder.cpp include/decoder.h include/encoder.h include/qpsk.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c tests/test_decoder.cpp -o $(BUILD_DIR)/test_decoder.o

$(BUILD_DIR)/test_channel.o: tests/test_channel.cpp include/channel.h include/qpsk.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c tests/test_channel.cpp -o $(BUILD_DIR)/test_channel.o

$(BUILD_DIR)/test_simulation.o: tests/test_simulation.cpp include/simulation.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c tests/test_simulation.cpp -o $(BUILD_DIR)/test_simulation.o

$(APP): $(APP_OBJ)
	$(CXX) $(CXXFLAGS) $(APP_OBJ) -o $(APP)

test: $(TEST_APP)

$(TEST_APP): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $(TEST_APP)

run: $(APP)
	./$(APP)

run_tests: $(TEST_APP)
	./$(TEST_APP)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

retest: clean test

.PHONY: all test run run_tests clean rebuild retest