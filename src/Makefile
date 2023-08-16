CC = gcc
CFLAGS = -Wall -g
SRCS = main.c linkedlist.c menu.c
OBJS = $(SRCS:.c=.o)


all: addresssbook

addressbook: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJS) addressbook
