CC      = gcc
# CHANGE: Point to 'source' instead of 'include'
CFLAGS  = -I -Wall -Wextra -g
OBJDIR  = obj


OBJS = $(OBJDIR)/main.o $(OBJDIR)/menu.o $(OBJDIR)/student.o
TARGET = task_assessment

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule for main.o
$(OBJDIR)/main.o: main.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for objects in the source folder
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean