.PHONY: format clang-format

format: clang-format

clang-format: include/iestade.hpp
	clang-format -i $^
