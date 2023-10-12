.PHONY: all, clean, format
PROJECT = Calc
CXX  = g++
CFLAGS = -Wall -std=c++14 -O2 -DNDEBUG
LDFLAGS = -l boost_program_options

all: $(PROJECT)

$(PROJECT): $(PROJECT).cpp
	$(CXX) $(CFLAGS) $<  -o $@ $(LDFLAGS)
	
format:
	astyle $(PROJECT).cpp
	
clean:
	rm -f Calc

