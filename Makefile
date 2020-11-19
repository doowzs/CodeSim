CXX = clang++
CXXFLAGS = -ggdb3 -Wall -MMD -std=c++17 -I$(shell pwd)
LDFLAGS = -lm -lclang -lclang-cpp -lLLVM
ifeq ($(shell uname), Darwin)
	CXXFLAGS += -DLLVM_PREFIX=/usr/local/opt/llvm
	CXXFLAGS += -I/usr/local/opt/llvm/include
	LDFLAGS += -L/usr/local/opt/llvm/lib
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
