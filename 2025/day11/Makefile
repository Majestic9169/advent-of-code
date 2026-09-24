CXX := g++
CXXFLAGS := -std=c++23 -Wall -g \
						-Wextra -Werror -Wshadow \
						-Wconversion -Wunreachable-code \
						-Wfloat-equal -Weffc++ \
						-Wnon-virtual-dtor \
						-Wold-style-cast \
						-Woverloaded-virtual -O2
SRCS := $(wildcard ./*.cpp)
OBJS := $(SRCS:.cpp=.out)

all: $(OBJS)

run: ${OBJS}
	@for obj in ${OBJS}; do \
		./$$obj; \
	done

%.out: %.cpp
	@${CXX} ${CXXFLAGS} $< -o $@
	@chmod +x $@

clean:
	-@rm -rf ./*.out

.PHONY: all clean
