BUILDDIR := build
DEBUGDIR := debug

SRCS := $(shell find src -name '*.c')

main: src/main.c
	mkdir -p $(BUILDDIR)
	gcc -o $(BUILDDIR)/database $(SRCS)

debug: src/main.c
	mkdir -p $(DEBUGDIR)
	gcc -g -o $(DEBUGDIR)/database $(SRCS)

clean:
	rm -r $(BUILDDIR)
	rm -r $(DEBUGDIR)