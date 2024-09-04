.PHONY: \
	all \
	examples \
	format \
	format-cpp \
	format-json \
	lint \
	lint-cpp \
	clean

all: examples

examples: config.o

config.o: examples/config.cpp
	g++ -Wall -Wextra -Werror -Wpedantic \
		-std=c++20 -O3 \
		-I./include \
		examples/config.cpp -o $@

format: format-cpp format-json

format-cpp: \
		include/iestaade.hpp \
		examples/config.cpp
	clang-format -i $^

format-json: examples/config.json
	jq . examples/config.json | sponge examples/config.json

lint: lint-cpp

lint-cpp: include/iestaade.hpp
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
