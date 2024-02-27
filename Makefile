NAME	=	miniRT

CFLAGS	=	-Wall -Werror -Wextra -g -O3 -Ofast

DFLAGS	=	-Wall -Werror -Wextra -g

LIBMLX_PATH	=	./lib/MLX42

LIBMLX		=	$(LIBMLX_PATH)/build/libmlx42.a

LIBFT_PATH	=	./lib/libft

LIBFT		=	$(LIBFT_PATH)/libft.a

DIR_OBJ	=	obj

LIBS	= 	$(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm

HEADERS=	-I ./includes -I $(LIBMLX_PATH)/include -I $(LIBFT_PATH)/include

SRCS =	main.c	\
				keypress_handle.c \
				free/free_functions.c	\
				free/free_obj.c	\
				parsing/ambiant_light.c \
				parsing/camera.c \
				parsing/choose_component.c \
				parsing/cylinder.c	\
				parsing/light.c \
				parsing/light_list.c \
				parsing/obj.c \
				parsing/obj_type.c \
				parsing/obj_utils.c \
				parsing/data_parsing.c \
				parsing/parsing.c \
				parsing/scene.c \
				parsing/direction_init.c \
				parsing/parsing_utils.c \
				parsing/check_input.c \
				parsing/check_input2.c \
				parsing/check_input3.c \
				parsing/plane.c	\
				parsing/sphere.c 	\
				parsing/ellipsoid.c 	\
				parsing/ellipsoid_utils.c 	\
				calculations/coordinate_frame_transform.c 	\
				parsing/triangle.c 	\
				calculations/light_calculations.c \
				calculations/light_rgb.c \
				calculations/diffuse_light.c \
				calculations/specular.c \
				calculations/sphere_calculations.c 	\
				calculations/cylinder_calculations.c 	\
				calculations/cylinder_calculations2.c 	\
				calculations/ellipsoid_calculations.c 	\
				calculations/cylinder_shadow.c 	\
				calculations/triangle_shadow.c 	\
				calculations/triangle_calculations.c 	\
				calculations/normal.c \
				calculations/vector.c \
				calculations/vector_calculations.c \
				calculations/shadow.c \
				calculations/quaternions.c \
				calculations/bump_map.c \
				calculations/bump_map2.c \
				calculations/ellipsoid_normal.c	\
				render/color.c	\
				render/normal_color.c	\
				render/hit_functions.c \
				render/render.c	\
				render/ray.c \
				render/checkerboard.c \
				render/checkerboard2.c \
				render/texture.c \
				render/texture2.c \
				moves/rotation.c \
				moves/vector_rotation.c \
				moves/rotation_obj.c \
				moves/cylinder_move.c \
				moves/plane_move.c \
				moves/sphere_move.c \
				moves/ellipsoid_move.c \
				moves/triangle_move.c \
				moves/rotate_around_triangle.c \
				moves/world_move.c \
				moves/light_rotation.c \
				moves/move_obj.c \
				moves/translate.c \
				utils/math_utils.c \
				utils/rgba.c \
				utils/structs_utils.c \
				utils/utils.c \
				utils/utils_calc.c \

SRCS:=	$(SRCS:%=srcs/%)

OBJS:=	$(addprefix $(DIR_OBJ)/, $(SRCS:.c=.o))

CC	:= clang

all: $(LIBMLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $@
	@clear
	@make header --no-print-directory

$(DIR_OBJ)/%.o: %.c 
	@mkdir -p $(@D)
	@$(CC) $(DFLAGS) $(HEADERS) -c $< -o $@   

$(LIBMLX): 
	@if [ ! -d './lib/MLX42/' ] || [ -z "$(ls  -a ./lib/MLX42/)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git ./lib/MLX42; \
	fi
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build -j4

$(LIBFT): 
	@make -C $(LIBFT_PATH)


clean: 
	@rm -rf $(DIR_OBJ)
	@rm -rf $(LIBMLX_PATH)/build
	@make fclean -C $(LIBFT_PATH)

fclean: clean 
	@rm -f $(NAME)
	@rm -rf $(LIBMLX_PATH)

re: clean all

.PHONY: all, clean, fclean, re, libmlx

-include header.mk
