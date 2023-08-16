#BIN := addressbook
CFLAGS := -Wall -g
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

.PHONY: clean all

all: $(OBJS)

#$(BIN): $(OBJS)
#	$(CC) $(CFLAGS) -llinkedlist -L../lib -o $@ $^
	
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 


clean:
	$(RM) $(OBJS)
