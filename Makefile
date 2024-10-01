# Makefile for project with main.cpp in root directory
# and source/header files in 'classes' directory

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++20 -Wall

# Directories
SRCDIR := classes
BUILDDIR := build
TARGET := main

# Files to compile
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Main target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

.PHONY: clean

clean:
	rm -rf $(BUILDDIR) $(TARGET)