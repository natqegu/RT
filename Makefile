#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/26 19:06:13 by vkarpova          #+#    #+#              #
#    Updated: 2018/09/26 19:06:14 by vkarpova         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = RT

DIR = objects

PATH_INC = ./libft/includes/

CC = gcc

FLAGS = -Wall -Wextra -Werror -O3

INCLUDES = -I$(HEADERS_DIRECTORY)

HEADERS_LIST = rt.h

HEADERS_DIRECTORY = ./includes/

HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./sources/

SRC_C = calc_vector.c\
		do.c\
		event.c\
		fig_data.c\
		intersect_basic.c\
		light.c\
		main.c\
		normals.c\
		parsing.c\
		rotation.c\
		useful_staff.c

SRC_O = $(addprefix objects/,$(SRC_C:.c=.o))

$(DIR)/%.o: $(SOURCES_DIRECTORY)%.c $(HEADERS)
	gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

all: $(NAME)

$(DIR):
	mkdir -p $(DIR)

$(NAME): $(DIR) $(SRC_O)
	make -C libft/
	$(CC) -o $(NAME) $(SRC_O) -lm -L libft/ -lft -lmlx -framework OpenGL -framework AppKit

clean:
	make -C libft/ clean
	/bin/rm -rf $(DIR)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

