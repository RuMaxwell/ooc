default: compile link run

compile:
	@echo Compiling...
	@gcc -g -c ./src/*.c ./test.c
	@echo Compile Succeeded.
	@echo

link:
	@echo Linking...
	@gcc -o test ./*.o
	@echo Link Succeeded.
	@echo

run:
	./test

clean:
	rm ./*.o
	rm ./test
