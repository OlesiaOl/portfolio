CXX = g++
CXXFLAGS = -O2 -std=c++17 -pedantic -Wall -Wextra -Werror -Iinclude

EXE = lab-13_parallel-sort
SRCDIR = src
BINDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

$(EXE): $(BINDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -lpthread -o $(EXE) $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(EXE)

.PHONY: clean all

