DAYS := $(sort $(dir $(wildcard */.)))

.PHONY: all run bench ${DAYS}

all:
	@for day in ${DAYS}; do \
		echo "=== $$day ==="; \
		${MAKE} -C $$day all || exit 1; \
	done

run: 
	@for day in ${DAYS}; do \
		echo "=== $$day ==="; \
		${MAKE} -C $$day run || exit 1; \
	done

BENCH_CMDS := $(shell for d in day*; do echo "'make -C $$d run'"; done)

bench:
	hyperfine --warmup 1 --style full --export-markdown temp.md $(BENCH_CMDS)

clean:
	@-for day in ${DAYS}; do \
		echo "=== $$day ==="; \
		${MAKE} -C $$day clean || exit 1; \
	done
