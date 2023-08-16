CFLAGS := -Wall -g
SRC_DIR := ./src
LIB_DIR := ./lib
DIRS := $(SRC_DIR) $(LIB_DIR)
LDFLAGS := -Wl,-rpath=$(LIB_DIR)
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRCS))
TARGET := addressbook

.PHONY: all clean $(DIRS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) -llinkedlist $(LDFLAGS)

$(DIRS):
	$(MAKE) -C $@

$(OBJS): $(SRCS) $(DIRS)

clean:
	for dir in $(DIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(RM) $(TARGET) $(OBJS)
