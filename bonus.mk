HEADERS_BONUS	=	-I ./bonus/includes -I $(LIBMLX_PATH)/include -I $(LIBFT_PATH)/include

SRCS_BONUS	=	src/main_bonus.c	\
				src/keypress_handle_bonus.c \
				src/free/free_functions_bonus.c	\
				src/free/free_obj_bonus.c	\
				src/parsing/ambiant_light_bonus.c \
				src/parsing/camera_bonus.c \
				src/parsing/choose_component_bonus.c \
				src/parsing/cylinder_bonus.c	\
				src/parsing/light_bonus.c \
				src/parsing/light_list_bonus.c \
				src/parsing/obj_bonus.c \
				src/parsing/obj_type_bonus.c \
				src/parsing/obj_utils_bonus.c \
				src/parsing/data_parsing_bonus.c \
				src/parsing/parsing_bonus.c \
				src/parsing/scene_bonus.c \
				src/parsing/direction_init_bonus.c \
				src/parsing/parsing_utils_bonus.c \
				src/parsing/check_input_bonus.c \
				src/parsing/check_input2_bonus.c \
				src/parsing/check_input3_bonus.c \
				src/parsing/plane_bonus.c	\
				src/parsing/sphere_bonus.c 	\
				src/parsing/ellipsoid_bonus.c 	\
				src/calculations/coordinate_frame_transform_bonus.c 	\
				src/parsing/triangle_bonus.c 	\
				src/calculations/light_calculations_bonus.c \
				src/calculations/light_rgb_bonus.c \
				src/calculations/diffuse_light_bonus.c \
				src/calculations/specular_bonus.c \
				src/calculations/sphere_calculations_bonus.c 	\
				src/calculations/cylinder_calculations_bonus.c 	\
				src/calculations/cylinder_calculations2_bonus.c 	\
				src/calculations/ellipsoid_calculations_bonus.c 	\
				src/calculations/cylinder_shadow_bonus.c 	\
				src/calculations/triangle_shadow_bonus.c 	\
				src/calculations/triangle_calculations_bonus.c 	\
				src/calculations/normal_bonus.c \
				src/calculations/vector_bonus.c \
				src/calculations/vector_calculations_bonus.c \
				src/calculations/shadow_bonus.c \
				src/calculations/quaternions_bonus.c \
				src/calculations/bump_map_bonus.c \
				src/calculations/bump_map2_bonus.c \
				src/calculations/ellipsoid_normal_bonus.c	\
				src/render/color_bonus.c	\
				src/render/normal_color_bonus.c	\
				src/render/hit_functions_bonus.c \
				src/render/render_bonus.c	\
				src/render/ray_bonus.c \
				src/render/checkerboard_bonus.c \
				src/render/checkerboard2_bonus.c \
				src/render/texture_bonus.c \
				src/render/texture2_bonus.c \
				src/moves/rotation_bonus.c \
				src/moves/vector_rotation_bonus.c \
				src/moves/rotation_obj_bonus.c \
				src/moves/cylinder_move_bonus.c \
				src/moves/plane_move_bonus.c \
				src/moves/sphere_move_bonus.c \
				src/moves/ellipsoid_move_bonus.c \
				src/moves/triangle_move_bonus.c \
				src/moves/rotate_around_triangle_bonus.c \
				src/moves/world_move_bonus.c \
				src/moves/light_rotation_bonus.c \
				src/moves/move_obj_bonus.c \
				src/moves/translate_bonus.c \
				src/utils/math_utils_bonus.c \
				src/utils/rgba_bonus.c \
				src/utils/structs_utils_bonus.c \
				src/utils/utils_bonus.c \
				src/utils/utils_calc_bonus.c \

SRCS_BONUS	:=	$(SRCS_BONUS:%=bonus/%)

OBJS_BONUS	:=	$(addprefix $(DIR_OBJ)/, $(SRCS_BONUS:.c=.o))

$(DIR_OBJ)/%_bonus.o: %_bonus.c 
	@mkdir -p $(@D)
	@$(CC) $(DFLAGS) $(HEADERS_BONUS) -c $< -o $@

bonus: $(LIBMLX) $(LIBFT) $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS_BONUS) -o miniRT_bonus

clean_bonus:
	@rm -rf $(LIBMLX_PATH)/build
	@make clean -C $(LIBFT_PATH)
	@rm -rf $(DIR_OBJ)

fclean_bonus: clean_bonus
	@rm -f miniRT_bonus

re_bonus: clean_bonus bonus 

.PHONY: clean_bonus, fclean_bonus, re_bonus, bonus
