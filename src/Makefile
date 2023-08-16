CFLAGS := -Wall -g
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

.PHONY: clean all

all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 


clean:
	$(RM) $(OBJS)
