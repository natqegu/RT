NAME = RT

DIR = objects

FLAGS = -g -Wextra -Werror -Wall

INCLUDES = -I$(HEADERS_DIRECTORY)

HEADERS_DIRECTORY = ./includes/

HEADERS_LIST = rt.h

HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./sources/

SRC_C = brights.c\
		central.c\
		check_arg.c\
		check_arg_1.c\
		check_arg_2.c\
		parse_complex.c\
		parse_cone.c\
		parse_cylinder.c\
		parse_plane.c\
		parse_sphere.c\
		parse_tri.c\
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
		bright_sphere.c\
		bright_plane.c\
		bright_tri.c\
		bright_cone.c\
		bright_cylinder.c\
		re_trans.c\

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
