DAYS := $(sort $(dir $(wildcard */.)))

.PHONY: all run bench ${DAYS}

all: run

run:
	@for day in ${DAYS}; do \
		echo "=== $$day ==="; \
		${MAKE} -C $$day || exit 1; \
	done

BENCH_CMDS := $(shell for d in day*; do echo "'make -C $$d run'"; done)

bench:
	hyperfine --warmup 1 --style full $(BENCH_CMDS)

clean:
	@for day in ${DAYS}; do \
		echo "=== $$day ==="; \
		${MAKE} -C $$day clean || exit 1; \
	done
