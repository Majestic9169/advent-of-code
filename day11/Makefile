CXX := g++
CXXFLAGS := -std=c++17 -Wall -g \
						-Wextra -Werror -Wshadow \
						-Wconversion -Wunreachable-code \
						-Wfloat-equal -Weffc++ \
						-Wnon-virtual-dtor \
						-Wold-style-cast \
						-Woverloaded-virtual -O2
SRCS := $(wildcard ./*.cpp)
OBJS := $(SRCS:.cpp=.out)
PY_SRCS := $(wildcard ./*.py)

all: $(OBJS) input
	@for f in $(PY_SRCS); do python $$f; done

%.out: %.cpp
	@${CXX} ${CXXFLAGS} $< -o $@
	@chmod +x $@
	./$@
	@echo ""

clean:
	-@rm -rf ./*.out

.PHONY: all clean
