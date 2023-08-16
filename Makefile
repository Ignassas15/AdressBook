CFLAGS := -Wall -g

SRC_DIR := ./src
LIB_DIR := ./lib
DIRS := $(SRC_DIR) $(LIB_DIR)


OBJS = $(wildcard $(SRC_DIR)/*.o)
TARGET := addressbook

.PHONY: all $(LIB_DIRS) clean

all: $(TARGET)




$(TARGET): $(OBJS) $(DIRS)
	$(CC) $(CFLAGS) -o $@ $^ -l$(LIB_DIR) -llinkedlist

$(DIRS):
	$(MAKE) -C $@


#	$(CC) $(CFLAGS) -llinkedlist -L../lib -o $@ $^

clean:
	for dir in $(LIB_DIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(RM) $(TARGET)




