.PHONY: run
all : ./grammar/hl.g ./src/main.cpp
	make clean
	antlr3 ./grammar/hl.g
	mv ./hl.tokens ./grammar/
	g++ -I./include/ -I./grammar/ ./src/main.cpp ./src/*.cc ./grammar/*.c -lantlr3c -o ./bin/hython

clean:
	-rm -rf ./grammar/*.c ./grammar/*.h ./grammar/hl.tokens
	-rm -rf ./bin/hython

run:
	./bin/hython ./test/input.hl
