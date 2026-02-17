JS_SRCS := $(wildcard ./*.js)

all: 
	@for f in $(JS_SRCS); do node $$f; done

clean:
	-@rm -rf ./*.out

.PHONY: all clean
