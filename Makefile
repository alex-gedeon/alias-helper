all: install

install:
	@g++ src/alh.cpp src/util.cpp src/Table.cpp -std=c++11 -Wall -Werror -Wextra -pedantic -O3 -DNDEBUG -o src/alh
	@cp src/alh /usr/local/bin/
