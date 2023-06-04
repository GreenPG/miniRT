NAME	=	miniRT

CFLAGS	=	-Wall -Werror -Wextra -g -O3 -Ofast

DFLAGS	=	-Wall -Werror -Wextra -g

LIBMLX	=	./lib/MLX42

LIBFT	=	./lib/libft

HEADERS	=	-I ./mandatory/includes -I $(LIBMLX)/include -I $(LIBFT)/include

LIBS	= 	$(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	=	mandatory/src/main.c	\
			mandatory/src/keypress_handle.c \
			mandatory/src/free_functions.c	\
			mandatory/src/parsing/ambiant_light.c \
			mandatory/src/parsing/camera.c \
			mandatory/src/parsing/choose_component.c \
			mandatory/src/parsing/cylinder.c	\
			mandatory/src/parsing/light.c \
			mandatory/src/parsing/obj.c \
			mandatory/src/parsing/obj_utils.c \
			mandatory/src/parsing/parsing.c \
			mandatory/src/parsing/parsing_utils.c \
			mandatory/src/parsing/plane.c	\
			mandatory/src/parsing/sphere.c 	\
			mandatory/src/calculations/light_calculations.c \
			mandatory/src/calculations/sphere_calculations.c 	\
			mandatory/src/calculations/cylinder_calculations.c 	\
			mandatory/src/calculations/cylinder_calculations2.c 	\
			mandatory/src/calculations/cylinder_shadow.c 	\
			mandatory/src/calculations/normal.c \
			mandatory/src/calculations/vector.c \
			mandatory/src/calculations/shadow.c \
			mandatory/src/calculations/ray_transforms.c \
			mandatory/src/render/color.c	\
			mandatory/src/render/normal_color.c	\
			mandatory/src/render/hit_functions.c \
			mandatory/src/render/render.c	\
			mandatory/src/render/ray.c \
			mandatory/src/moves/rotation.c \
			mandatory/src/moves/cylinder_move.c \
			mandatory/src/moves/plane_move.c \
			mandatory/src/moves/sphere_move.c \
			mandatory/src/moves/light_rotation.c \
			mandatory/src/moves/move_obj.c \
			mandatory/src/moves/translate.c \
			mandatory/src/utils/math_utils.c \
			mandatory/src/utils/rgba.c \
			mandatory/src/utils/structs_utils.c \
			mandatory/src/utils/utils.c \

OBJS	= ${SRCS:.c=.o}

CC	:= clang

all: libmlx libft $(NAME)

-include header.mk

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

%.o: %.c 
	@$(CC) $(CFLAGS) -o ./obj/$@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(addprefix ./obj/,$(OBJS)) $(LIBS) $(HEADERS) -o $(NAME)
	@clear
	@make header --no-print-directory

clean: clean_bonus
	@rm -f $(addprefix ./obj/,$(OBJS))
	@rm -rf $(LIBMLX)/build
	@make clean -C $(LIBFT)

fclean: clean fclean_bonus
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx

-include bonus.mk
-include test.mk