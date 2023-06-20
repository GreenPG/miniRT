NAME	=	miniRT

CFLAGS	=	-Wall -Werror -Wextra -g -O3 -Ofast

DFLAGS	=	-Wall -Werror -Wextra -g

LIBMLX_PATH	=	./lib/MLX42

LIBMLX		=	$(LIBMLX_PATH)/build/libmlx42.a

LIBFT_PATH	=	./lib/libft

LIBFT		=	$(LIBFT_PATH)/libft.a

DIR_OBJ	=	obj

HEADERS	=	-I ./mandatory/includes -I $(LIBMLX_PATH)/include -I $(LIBFT_PATH)/include

LIBS	= 	$(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm

SRCS	:=	src/main.c	\
			src/keypress_handle.c \
			src/free_functions.c	\
			src/parsing/ambiant_light.c \
			src/parsing/camera.c \
			src/parsing/choose_component.c \
			src/parsing/cylinder.c	\
			src/parsing/light.c \
			src/parsing/obj.c \
			src/parsing/obj_utils.c \
			src/parsing/parsing.c \
			src/parsing/parsing_utils.c \
			src/parsing/plane.c	\
			src/parsing/sphere.c 	\
			src/parsing/vector_parsing.c 	\
			src/calculations/light_calculations.c \
			src/calculations/sphere_calculations.c 	\
			src/calculations/cylinder_calculations.c 	\
			src/calculations/cylinder_calculations2.c 	\
			src/calculations/cylinder_shadow.c 	\
			src/calculations/normal.c \
			src/calculations/vector.c \
			src/calculations/quaternions.c \
			src/calculations/shadow.c \
			src/render/color.c	\
			src/render/normal_color.c	\
			src/render/hit_functions.c \
			src/render/render.c	\
			src/render/ray.c \
			src/moves/rotation.c \
			src/moves/vector_rotation.c \
			src/moves/cylinder_move.c \
			src/moves/plane_move.c \
			src/moves/sphere_move.c \
			src/moves/light_rotation.c \
			src/moves/move_obj.c \
			src/moves/translate.c \
			src/utils/math_utils.c \
			src/utils/rgba.c \
			src/utils/structs_utils.c \
			src/utils/utils.c \

SRCS	:=	$(SRCS:%=mandatory/%)

OBJS		:=	$(addprefix $(DIR_OBJ)/, $(SRCS:%.c=%.o))

CC	:= clang

all: $(LIBMLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $@
	@clear
	@make header --no-print-directory

$(DIR_OBJ)/%.o: %.c 
	mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@   

$(LIBMLX): 
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build -j4

$(LIBFT): 
	@make -C $(LIBFT_PATH)


clean: clean_bonus
	@rm -rf 
	@rm -rf $(LIBMLX_PATH)/build
	@make fclean -C $(LIBFT_PATH)

fclean: clean fclean_bonus
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx

-include bonus.mk
-include test.mk
-include header.mk
