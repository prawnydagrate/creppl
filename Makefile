# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I./include -g

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = build/obj
BINDIR = build/bin

# Files
SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(SRCFILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/project

# Targets
all: $(EXEC)

# Linking
$(EXEC): $(OBJFILES)
	$(CC) $(OBJFILES) -o $(EXEC)

# Compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Phony targets
.PHONY: all clean
