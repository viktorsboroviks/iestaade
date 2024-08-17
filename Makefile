.PHONY: \
	all \
	examples \
	format \
	clang-format \
	jq \
	lint \
	cppcheck \
	clean

all: examples

examples: config.o

examples-graph: graph.o examples/graph_config.json
	./graph.o
	python3 scripts/plot_graph.py examples/graph_config.json

config.o: examples/config.cpp
	g++ -Wall -Wextra -Werror -Wpedantic \
		-std=c++20 -O3 \
		-I./include \
		examples/config.cpp -o $@

format: clang-format jq

clang-format: \
		include/iestade.hpp \
		examples/config.cpp
	clang-format -i $^

jq: examples/config.json
	jq . examples/config.json | sponge examples/config.json

lint: cppcheck

cppcheck: include/iestade.hpp
	cppcheck \
		--enable=warning,portability,performance \
		--enable=style,information \
		--enable=missingInclude \
		--inconclusive \
		--library=std,posix,gnu \
		--platform=unix64 \
		--language=c++ \
		--std=c++20 \
		--inline-suppr \
		--check-level=exhaustive \
		--suppress=missingIncludeSystem \
		--suppress=checkersReport \
		--checkers-report=cppcheck_report.txt \
		-I./include \
		$^

clean:
	rm -rf `find . -name "*.o"`
