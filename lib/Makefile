CFLAGS := -Wall -fPIC
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)


TARGET := liblinkedlist.so 

.PHONY: clean all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $@ $^ 

%.o : %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS) $(TARGET)




