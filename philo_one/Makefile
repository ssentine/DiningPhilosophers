NAME = philo_one
FLAGS = -Wall -Wextra -Werror
SRCS_LIST = main.c \
			philo_life.c \
			print_msg.c \
			monitor.c \
			utils.c \
			libft.c
SRCS = $(addprefix srcs/, ${SRCS_LIST})
OBJS = $(SRCS:.c=.o)
HEADER = includes
.PHONY: all clean fclean re

all: $(NAME)
	
$(NAME): 	$(OBJS)
			gcc $(FLAGS) -I $(HEADER) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all