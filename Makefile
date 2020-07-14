install:
	# Making /local/ folder and compiling /src/table_driver.exe.
	@test -d $(LOCAL_DIR) || mkdir $(LOCAL_DIR)
	@g++ src/main.cpp -lstdc++fs -std=c++11 src/Table.cpp -o src/table_driver.exe

mkfile_path=$(abspath $(lastword $(MAKEFILE_LIST)))
LOCAL_DIR="$(PWD)/local/"

all: clean install

local: src/main.cpp src/Table.cpp src/Table.h
	# Helpful for local development, users shouldn't need to use this
	@g++ src/main.cpp -lstdc++fs src/Table.cpp -DDEBUG -g -o src/table_driver.exe
	@./src/table_driver.exe -t alias -f $(PWD)

clean:
	@rm -f *.exe
	@rm -f src/*.exe
	@rm -f testing/*.exe
