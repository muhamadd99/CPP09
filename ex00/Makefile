CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
NAME = btc

INC = BitcoinExchange.hpp

SRC = BitcoinExchange.cpp \
	  main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(INC)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

PHONY: all clean fclean re