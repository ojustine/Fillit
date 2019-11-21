# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojustine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 13:27:35 by ojustine          #+#    #+#              #
#    Updated: 2019/11/21 13:27:43 by ojustine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
NAME = fillit

FILES = \
			algorithm_x \
			create_cols_rows \
			destroy_matrix \
			error_exit \
			get_next_fig \
			get_puzzle \
			link_matrix \
			main \
			print_solution \
			solve

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o fillit $(OBJS)

.c.o : fillit.h
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
