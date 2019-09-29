NAME = RT

DIR = objects

FLAGS = -g #-Wextra -Werror -Wall

INCLUDES = -I$(HEADERS_DIRECTORY)

HEADERS_DIRECTORY = ./includes/

HEADERS_LIST = rt.h

HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./sources/

SRC_C = brights.c\
		bright_plane.c\
		bright_sphere.c\
		central.c\
		check_arg.c\
		check_arg_1.c\
		check_arg_2.c\
		check_arg_3.c\
		check_arg_4.c\
		check_arg_5.c\
		check_arg_6.c\
		check_arg_7.c\
		check_arg_8.c\
		check_arg_9.c\
		color.c\
		create_points.c\
		effects.c\
		entex.c\
		events.c\
		events2.c\
		ta_du_zaebal.c\
		free_points.c\
		hits.c\
		init_data.c\
		init_data2.c\
		initialize_points.c\
		lin_alg.c\
		linalg1.c\
		linalg2.c\
		one.c\
		main.c\
		memory.c\
		menu.c\

SRC_O = $(addprefix objects/,$(SRC_C:.c=.o))

$(DIR)/%.o: $(SOURCES_DIRECTORY)%.c $(HEADERS)
	gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

all: $(NAME)

$(DIR):
	mkdir -p $(DIR)

$(NAME): $(DIR) $(SRC_O)
	make -C libft/
	$(CC) -o $(NAME) $(SRC_O) -lm -L libft/ -lft -lmlx -framework OpenGL -framework AppKit -lpthread

clean:
	make -C libft/ clean
	rm -rf $(DIR)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all
