cc = gcc
CFLAGS = -Wall -g
FLEX = flex
BISON = bison

all: setlang_compiler

setlang_compiler: lex.yy.c setlang.tab.c symbol_table.c
	$(cc) $(CFLAGS) -o $@ $^

lex.yy.c: setlang.l setlang.tab.h
	$(FLEX) setlang.l

setlang.tab.c setlang.tab.h: setlang.y
	$(BISON) -d -t setlang.y

setlang_runtime.o: setlang_runtime.c setlang_runtime.h
	$(cc) $(CFLAGS) -c setlang_runtime.c

clean:
	del setlang_compiler.exe *.o *.yy.c setlang.tab.c setlang.tab.h

.PHONY: all clean