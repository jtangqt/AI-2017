BINFILE = checkers.out
CXX = g++
CXXFLAGS = --std=c++11

SOURCES = $(wildcard src/*.cpp)

.PHONY: run clean

$(BINFILE): $(SOURCES)
	@echo Building $(BINFILE)...
	@$(CXX) $(CXXFLAGS) -o $@ src/*.cpp -I includes

run: $(BINFILE)
	@echo Executing $(BINFILE)...
	@./$(BINFILE)

clean:
	@echo Removing $(BINFILE)...
	@rm -f $(BINFILE)
