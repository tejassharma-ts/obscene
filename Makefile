BINARY=obscene
CODEDIRS=. lib
INCDIRS=. ./include/ # can be list

CC=gcc
CFLAGS=-Wall -Wextra -g -I. -I./include 

# generate a list of .c files in (CODEDIRS)
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))

# regular expression replacement
OBJECTS=$(patsubst %.c,%.o,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

# only want the .c file dependency here, thus $< instead of $^
%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

