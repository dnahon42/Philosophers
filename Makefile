NAME        =   philosophers
CC          =   cc
CFLAGS      =   -g3 -O0 -Wall -Wextra -Werror

RM          =   rm -f

SRC_DIR     =   ./srcs
SRC         =   ./srcs/philosophers.c

INCLUDES    =   ./includes/philosophers.h

OBJ         =   $(SRC:.c=.o)

# Color codes
GREEN       =   \033[0;32m
YELLOW      =   \033[0;33m
RED         =   \033[0;31m
BLUE        =   \033[0;34m
PURPLE      =   \033[0;35m
CYAN        =   \033[0;36m
NC          =   \033[0m # No Color

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Building $(NC)$(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(INCLUDES)
	@echo "$(CYAN)Compiling $(NC)$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(CYAN)Cleaning object files"
	@$(RM) $(OBJ)

fclean: clean
	@echo "$(CYAN)Cleaning $(NC)$(NAME)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
