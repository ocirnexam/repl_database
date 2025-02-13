main: src/main.c
	mkdir -p build && cd build
	gcc -o database src/input_buffer/input_buffer.c src/main.c
	mv database build/database

clean:
	rm -r build