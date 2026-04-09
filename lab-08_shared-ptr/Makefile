CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude
LDFLAGS = 

EXE = lab-08_shared-ptr
SRCDIR = src
BINDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

$(EXE): $(BINDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(BINDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) -O2 -std=c++17 -Iinclude -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)
clean:
	rm -rf $(BINDIR) $(EXE)
.PHONY: clean all
