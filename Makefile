release: local

mkfile_path=$(abspath $(lastword $(MAKEFILE_LIST)))

all: testing local clean

testing: testing/test.cpp
	g++ testing/test.cpp -lstdc++fs -o testing/test.exe
	./testing/test.exe

local: src/main.cpp src/Table.cpp src/Table.h
	@g++ src/main.cpp -lstdc++fs src/Table.cpp -o src/table_driver.exe
	@echo "---Starting exe output---\n"
	@./src/table_driver.exe -t alias -f $(mkfile_path)

clean:
	rm -f *.exe
	rm -f src/*.exe
	rm -f testing/*.exe

install: clean
