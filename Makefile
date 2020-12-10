all: install

install:
	@g++ src/alh.cpp src/util.cpp src/Table.cpp -lstdc++fs -std=c++11 -o src/alh
	@cp src/alh /usr/local/bin/
