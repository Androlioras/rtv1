NAME = libsmlx.a
CC = gcc
SRCS = smlx_init.c\
	   smlx_destroy_window.c\
	   smlx_destroy_image.c\
	   smlx_put_image_to.c\
	   smlx_clear_image.c\
	   smlx_new_image.c\
	   smlx_draw_line.c\
	   smlx_pixel_put.c\
	   smlx_set_flags.c\
	   smlx_translate.c\
	   smlx_key_hook.c\
	   smlx_converts.c\
	   smlx_rotate.c\
	   smlx_create.c\
	   smlx_button.c\
	   smlx_matrix.c\
	   smlx_hooks.c\
	   smlx_draw_polygone.c\
	   smlx_draw_triangle.c\
	   smlx_get_fps.c\
	   colors.c
OBJS = $(SRCS:%.c=src/%.o)
FLAGS = -Wall -Wextra -Werror
INCLUDE = include
LIBFT = ../libft

.PHONY: clean fclean all re norme newline

all: $(NAME)

$(NAME): newline $(OBJS)
	@echo "\033[1A\033[K\033[38;5;214mmaking $@\033[0m"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[1A\033[K\033[38;5;214m$@ done\033[0m"

newline:
	@echo "\033[38;5;166mlibsmlx\033[0m\n"

%.o: %.c
	@echo "\033[1A\033[K\033[38;5;226mmaking $@\033[0m"
	@$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT)/include -o $@ -c $^

clean: newline
	@rm -f $(OBJS)
	@echo "\033[1A\033[K\033[38;5;45mobject files removed\033[0m\n"

fclean: newline clean
	@rm -f $(NAME)
	@echo "\033[1A\033[K\033[38;5;87m$(NAME) removed\033[0m\n"

norme:
	@norminette $(SRC) $(INCLUDE)

re: fclean all
