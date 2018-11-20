CXX = g++
STATIC_ANALYSIS = scan-build -v --force-analyze-debug-code
SANITIZE = -fsanitize=undefined

WARNINGS=-Wall -Wextra -Wshadow -Weffc++ -pedantic -pedantic-errors -Wc++14-compat -Wc++17-compat
#-fcheck-pointer-bounds
INCLUDES =
LIBS = -lstdc++fs -lpthread -lm
STD = c++17

all: test

.cpp:
	$(STATIC_ANALYSIS) $(CXX) $(INCLUDES) $(SANITIZE) -std=$(STD) -g -O3 $(WARNINGS) -o $@ $< $(LIBS)
