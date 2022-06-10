CC := gcc
CFLAGS := -Wall
YFLAG := -d -v
LEX_SRC := compiler_hw2.l
YAC_SRC := compiler_hw2.y
HEADER := compiler_hw_common.h
TARGET := myparser
VERBOSE := 0

all: ${TARGET}

${TARGET}: lex.yy.c y.tab.c
	${CC} ${CFLAGS} -o $@ $^

lex.yy.c: ${LEX_SRC} ${HEADER}
	lex $<

y.tab.c: ${YAC_SRC} ${HEADER}
	yacc ${YFLAG} $<

judge: all
	@judge -v ${VERBOSE}

clean:
	rm -f ${TARGET} y.tab.* y.output lex.*
