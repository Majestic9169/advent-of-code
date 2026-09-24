CXX := g++
CXXFLAGS := -std=c++17 -Wall -g \
						-Wextra -Werror -Wshadow \
						-Wconversion -Wunreachable-code \
						-Wfloat-equal -Weffc++ \
						-Wnon-virtual-dtor \
						-Wold-style-cast \
						-Woverloaded-virtual
SRCS := $(wildcard ./*.cpp)
OBJS := $(SRCS:.cpp=.out)

all: $(OBJS)

%.out: %.cpp
	@${CXX} ${CXXFLAGS} $< -o $@
	@chmod +x $@
	./$@
	@echo ""

clean:
	-@rm -rf ./*.out

.PHONY: all clean
