NAME = rtv1
FLAGS = -Wall -Wextra -Werror -Ofast
CC = gcc
LIBFT = libft
SMLX = smlx
LUA = lua
SRC =	rtv1.c\
		vector.c\
		quaternion.c\
		load_scene.c\
		load_scene_2.c\
		set_attribute.c\
		set_attribute_2.c\
		set_attribute_3.c\
		loop.c\
		flags.c\
		hooks.c
OBJ = $(SRC:%.c=src/%.o)

.PHONY: clean fclean all re norme newline $(LIBFT)/libft.a $(SMLX)/libsmlx.a

all: $(NAME)

newline:
	@echo "\033[38;5;166mrtv1\033[0m\n"

%.o: %.c
	@echo "\033[1A\033[K\033[38;5;226mmaking $@\033[0m"
	@$(CC) $(FLAGS) -I include -I $(LIBFT)/include -I $(SMLX)/include -o $@ -c $<

$(SMLX)/libsmlx.a:
	@make -C $(SMLX)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

$(NAME): $(SMLX)/libsmlx.a $(LIBFT)/libft.a newline $(OBJ)
	@echo "\033[1A\033[K\033[38;5;214mmaking $@\033[0m"
	@$(CC) $(FLAGS) -I include -I $(LIBFT)/include -I $(SMLX)/include -o $(NAME) $(OBJ) -L $(SMLX) -lsmlx -L $(LIBFT) -lft -lmlx -framework AppKit -framework OpenGL -framework OpenCL
	@echo "\033[1A\033[K\033[38;5;214m$@ done\033[0m"

clean:
	@echo "\033[38;5;166mrtv1\033[0m\n"
	@rm -f $(OBJ)
	@echo "\033[1A\033[K\033[38;5;45mobject files removed\033[0m\n"
	@make -C $(LIBFT) clean
	@make -C $(SMLX) clean

fclean: clean
	@echo "\033[38;5;166mrtv1\033[0m\n"
	@rm -f $(NAME)
	@echo "\033[1A\033[K\033[38;5;87m$(NAME) removed\033[0m\n"
	@make -C $(LIBFT) fclean
	@make -C $(SMLX) fclean

re: fclean all

norme: newline
	norminette $(OBJ:.o=.c) include
