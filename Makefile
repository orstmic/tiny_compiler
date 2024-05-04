exec = tac.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic


$(exec): $(objects)
	gcc $(objects) $(flags)  -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@


clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o
	-rm *.s

lint:
	clang-tidy src/*.c src/include/*.h
