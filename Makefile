CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g -MMD -MP

TARGET := mini_shell
SRCS := $(shell find . -type f \( -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" \))
OBJS := $(patsubst ./%,build/%,$(SRCS))
OBJS := $(OBJS:.cpp=.o)
OBJS := $(OBJS:.cc=.o)
OBJS := $(OBJS:.cxx=.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: %.cxx
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET) build

-include $(DEPS)
