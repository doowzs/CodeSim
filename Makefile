CXX = clang++
CXXFLAGS = -ggdb3 -Wall -MMD -std=c++17 -I$(shell pwd)
LDFLAGS = -lm
ifeq ($(shell uname), Darwin)
	CXXFLAGS += -DMACOS
	CXXFLAGS += -DLLVM_PREFIX=/usr/local/opt/llvm
	CXXFLAGS += -I/usr/local/opt/llvm/include
	LDFLAGS += -lclang -lclang-cpp -lLLVM
	LDFLAGS += -L/usr/local/opt/llvm/lib
else ifeq ($(shell uname), Linux)
	CXX = clang++-11
	CXXFLAGS += -I$(shell llvm-config-11 --prefix)/include
	LDFLAGS += -lclang-11 -lclang-cpp11 -lLLVM-11
	LDFLAGS += -L$(shell llvm-config-11 --prefix)/lib
endif

SRCS = $(wildcard */*.cpp)
OBJS = $(patsubst %.cpp,build/%.o,$(SRCS))
-include $(OBJS:.o=.d)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

codesim: $(OBJS)
	@echo "[LD] codesim"
	@$(CXX) $(LDFLAGS) -o $@ $^

.PHONY: all test clean
.DEFAULT_GOAL=all

all: codesim

test: all
	@./codesim -v tests/P1764/a.cpp tests/P1764/b.cpp

clean:
	@$(RM) -r build codesim
