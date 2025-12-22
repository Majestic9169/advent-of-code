DAYS := $(sort $(dir $(wildcard */.)))

all: ${DAYS}

${DAYS}:
	@cd $@ && make && make clean

.PHONY: all ${DAYS}
