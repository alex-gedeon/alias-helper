release: local

all: testing local clean

testing: testing/test.cpp
	g++ testing/test.cpp -lstdc++fs -o testing/test.exe
	./testing/test.exe

local: src/main.cpp
	g++ src/main.cpp -lstdc++fs -o src/main.exe
	./src/main.exe $(PWD)

clean:
	rm -f *.exe
	rm -f src/*.exe
	rm -f testing/*.exe