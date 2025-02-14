BUILDDIR := build

SRCS := $(shell find src -name '*.c')

main: src/main.c
	mkdir -p $(BUILDDIR)
	gcc -o $(BUILDDIR)/database $(SRCS)

clean:
	rm -r $(BUILDDIR)