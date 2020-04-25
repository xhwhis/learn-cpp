.PHONY: run
all : ./thirdpart/hl.g ./src/main.cpp
	java -jar ./thirdpart/antlr-3.4-complete.jar ./thirdpart/hl.g 
	mv ./thirdpart/*.h ./thirdpart/*.c ./haizei_gramma/
	mv ./hl.tokens ./haizei_gramma/
	g++ -I./include -I./haizei_gramma/ -DDEBUG ./src/main.cpp ./src/*.cc ./haizei_gramma/*.c -lantlr3c -o ./bin/hython

run:
	./bin/hython ./test_data/input.hl

clean:
	-rm -rf ./thirdpart/*.h ./thirdpart/*.c
	-rm -rf ./haizei_gramma/*
	-rm -rf ./hl.tokens
	-rm -rf ./bin/hython