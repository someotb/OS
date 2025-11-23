CC = g++
CFLAGS = -Wall

SRCDIR = src
BINDIR = bin

MAINS = $(shell grep -l "int main" $(SRCDIR)/*.cpp)
TARGETS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%,$(MAINS))

all: $(TARGETS)

$(BINDIR)/%: $(SRCDIR)/%.cpp | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR)/*