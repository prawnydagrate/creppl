CC = gcc
# CFLAGS = -Wall -Wextra -I./include -g
CFLAGS = -Wall -I./include -g

SRCDIR = src
INCDIR = include
OBJDIR = build/obj
BINDIR = build/bin

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(SRCFILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/creppl

$(EXEC): $(OBJFILES)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJFILES) -o $(EXEC)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

build: $(EXEC)

run:
	@./$(EXEC)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: build clean

all: $(EXEC)
