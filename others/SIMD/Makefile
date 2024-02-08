CXX = g++
OPTIM_LEV = -O0
CXXFLAGS = -g -std=c++11 -Wall $(OPTIM_LEV) -mcpu=native -fno-tree-vectorize -DNDEBUG -pthread
# CXXFLAGS = -std=c++11 -Wall $(OPTIM_LEV) -mcpu=native -DNDEBUG -pthread  
LDFLAGS = -lpthread -pthread
INCLUDES = -I./common

EXECUTABLES = baseline neon example test-baseline
SRC = $(wildcard src/*.cpp common/*.cpp)
EXAMPLE_SRC = $(wildcard neon_example/*.cpp common/*.cpp)

.PHONY: clean

all: $(EXECUTABLES)
	@echo $(EXECUTABLES) compiled!

baseline: $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

neon: $(SRC)
	$(CXX) -DVECTORIZED $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

example: $(EXAMPLE_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

clean:
	$(RM) -rf perf* *.bin *.txt *.dSYM *.out *.o *~ $(EXECUTABLES)

test-baseline: $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)
	./test-baseline > latency.txt
	size test-baseline > size.txt

test-neon: $(SRC)
	$(CXX) -DVECTORIZED $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)
	./test-neon > latency.txt
	size test-neon > size.txt

