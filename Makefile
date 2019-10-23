# Makefile Generique
#-Wall -W
EXT = cpp
CXX = g++
EXEC = MCvsW

CXXFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system


OBJDIR = obj
SRC = $(wildcard *.$(EXT))
OBJ = $(SRC:.$(EXT)=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))


all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.$(EXT)
	- mkdir -p $(OBJDIR)
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	@rm -rf $(OBJDIR)/*.o
	@rm -f $(EXEC)

install: $(EXEC)
	@cp $(EXEC) /usr/bin/
