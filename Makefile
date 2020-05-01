test: local

mkfile_path=$(abspath $(lastword $(MAKEFILE_LIST)))
LOCAL_DIR="$(PWD)/local/"

all: testing local clean

testing: testing/test.cpp
	g++ testing/test.cpp -lstdc++fs -o testing/test.exe
	./testing/test.exe

local: src/main.cpp src/Table.cpp src/Table.h
	@g++ src/main.cpp -lstdc++fs src/Table.cpp -DDEBUG -g -o src/table_driver.exe
	@./src/table_driver.exe -t alias -f $(PWD)

clean:
	@rm -f *.exe
	@rm -f src/*.exe
	@rm -f testing/*.exe

install:
	# Making local folder and compiling table driver exe.
	@test -d $(LOCAL_DIR) || mkdir $(LOCAL_DIR)
	@g++ src/main.cpp -lstdc++fs src/Table.cpp -o src/table_driver.exe
