.PHONY: \
	all \
	examples \
	format \
	clang-format \
	clean

all: examples

examples: config.o

examples_graph: graph.o examples/graph_config.json
	./graph.o
	python3 scripts/plot_graph.py examples/graph_config.json

config.o: examples/config.cpp
	g++ -Wall -Wextra -Werror -Wpedantic \
		-std=c++20 -O3 \
		-I./include \
		examples/config.cpp -o $@

format: clang-format

clang-format: \
		include/iestade.hpp \
		examples/config.cpp
	clang-format -i $^

clean:
	rm -rf `find . -name "*.o"`
