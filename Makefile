SRC	= $(wildcard *.c)

all	:	$(SRC)
		gcc -Wall -Wextra -Werror -g $^
