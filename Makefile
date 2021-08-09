NAME	= aya-client
SOURCE	= source
INCLUDE	= include

CFLAGS	= -Wall -pedantic -ffunction-sections

CXXFLAGS = -std=c++20 $(CFLAGS)

.PHONY: all clean

all:
	g++ $(CXXFLAGS) -I$(INCLUDE) $(SOURCE)/*.cpp $(SOURCE)/aya/*.cpp -o $(NAME)

clean:
	rm $(NAME)


