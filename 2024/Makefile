CXX := g++
CXXFLAGS := -std=c++20 -Wall -g \
						-Wextra -Wshadow \
						-Wconversion -Wunreachable-code \
						-Wfloat-equal -Weffc++ \
						-Wnon-virtual-dtor \
						-Wold-style-cast \
						-Woverloaded-virtual -O2
SRCS := $(wildcard ./*.cpp)

all: runner

runner: ${SRCS}
	@${CXX} ${CXXFLAGS} $^ -o $@
	@chmod +x ./$@

run: runner
	./$<

clean:
	-@rm -rf ./*.out runner

.PHONY: all clean
