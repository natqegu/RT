NAME = RT

DIR = objects

FLAGS = #-Wextra -Werror -Wall

INCLUDES = -I$(HEADERS_DIRECTORY)

HEADERS_DIRECTORY = ./includes/

HEADERS_LIST = rt.h

HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./sources/

SRC_C = brights.c\
		central.c\
		check_arg.c\
		color.c\
		create_points.c\
		entex.c\
		events.c\
		free_points.c\
		hits.c\
		init_data.c\
		initialize_points.c\
		lin_alg.c\
		linalg1.c\
		main.c\
		memory.c\

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
	rm -rf $(DIR)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all
