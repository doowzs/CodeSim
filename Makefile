CXX = clang++
CXXFLAGS = -ggdb3 -Wall -MMD -std=c++17
LDFLAGS = -lm -lclang
ifeq ($(shell uname), Darwin)
	CXXFLAGS += -I/usr/local/opt/llvm/include
	LDFLAGS += -L/usr/local/opt/llvm/lib
endif

SRCS = $(wildcard */*.cpp)
OBJS = $(patsubst %.cpp,build/%.o,$(SRCS))
-include $(OBJS:.o=.d)

codesim: $(OBJS)
	@echo "[LD] codesim"
	@$(CXX) $(LDFLAGS) -o $@ $^

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	@echo $(OS)
	@$(RM) -r build codesim
