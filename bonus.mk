HEADERS_BONUS	=	-I ./bonus/includes -I $(LIBMLX)/include -I $(LIBFT)/include

SRCS_BONUS	=	bonus/src/main_bonus.c	\
				bonus/src/keypress_handle_bonus.c \
				bonus/src/free_functions_bonus.c	\
				bonus/src/parsing/ambiant_light_bonus.c \
				bonus/src/parsing/camera_bonus.c \
				bonus/src/parsing/choose_component_bonus.c \
				bonus/src/parsing/cylinder_bonus.c	\
				bonus/src/parsing/light_bonus.c \
				bonus/src/parsing/light_list_bonus.c \
				bonus/src/parsing/obj_bonus.c \
				bonus/src/parsing/obj_utils_bonus.c \
				bonus/src/parsing/parsing_bonus.c \
				bonus/src/parsing/parsing_utils_bonus.c \
				bonus/src/parsing/plane_bonus.c	\
				bonus/src/parsing/sphere_bonus.c 	\
				bonus/src/calculations/light_calculations_bonus.c \
				bonus/src/calculations/sphere_calculations_bonus.c 	\
				bonus/src/calculations/cylinder_calculations_bonus.c 	\
				bonus/src/calculations/cylinder_calculations2_bonus.c 	\
				bonus/src/calculations/cylinder_shadow_bonus.c 	\
				bonus/src/calculations/normal_bonus.c \
				bonus/src/calculations/vector_bonus.c \
				bonus/src/calculations/shadow_bonus.c \
				bonus/src/calculations/ray_transforms_bonus.c \
				bonus/src/render/color_bonus.c	\
				bonus/src/render/normal_color_bonus.c	\
				bonus/src/render/hit_functions_bonus.c \
				bonus/src/render/render_bonus.c	\
				bonus/src/render/ray_bonus.c \
				bonus/src/moves/rotation_bonus.c \
				bonus/src/moves/cylinder_move_bonus.c \
				bonus/src/moves/plane_move_bonus.c \
				bonus/src/moves/sphere_move_bonus.c \
				bonus/src/moves/light_rotation_bonus.c \
				bonus/src/moves/move_obj_bonus.c \
				bonus/src/moves/translate_bonus.c \
				bonus/src/utils/math_utils_bonus.c \
				bonus/src/utils/rgba_bonus.c \
				bonus/src/utils/structs_utils_bonus.c \
				bonus/src/utils/utils_bonus.c \

OBJS_BONUS	=	${SRCS_BONUS:.c=.o}

%_bonus.o: %_bonus.c 
	@$(CC) $(CFLAGS) -o ./obj/$@ -c $< $(HEADERS_BONUS)

bonus: $(OBJS_BONUS)
	@$(CC) $(addprefix ./obj/,$(OBJS_BONUS)) $(LIBS) $(HEADERS_BONUS) -o minirt_bonus

clean_bonus:
	@rm -rf $(LIBMLX)/build
	@make clean -C $(LIBFT)
	@rm -f $(addprefix ./obj/,$(OBJS_BONUS))

fclean_bonus: clean
	@rm -f minirt_bonus

re_bonus: clean_bonus all_bonus

.PHONY: clean_bonus, fclean_bonus, re_bonus, bonus