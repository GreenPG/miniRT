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

define HEADER
██████████████████████████████████████████████████████
████                                              ████
███                                                ███
███                   \033[1;35m\e[1;46m▓▓▓▓▓▓▓▓▓▓▓▓\e[0m                 ███
██              \033[1;35m░░\e[1;46m████░░░░░░░░░░░░████\e[0m              ██
██            \033[1;35m░░\e[1;46m██▒▒░░░░░░░░░░░░░░░░░░██\e[0m            ██
██          \033[1;35m░░\e[1;46m██▒▒▒▒░░░░░░░░░░░░░░░░░░░░██\e[0m          ██
██         \033[1;35m\e[1;46m██▒▒▒▒░░░░░░░░░░░░░░    ░░░░░░██\e[0m         ██
██         \033[1;35m\e[1;46m██▒▒▒▒░░░░░░░░░░░░        ░░░░██\e[0m         ██
█        \033[1;35m\e[1;46m██▓▓▒▒▒▒░░░░░░░░░░░░        ░░░░░░██\e[0m        █
█        \033[1;35m\e[1;46m██▓▓▒▒▒▒░░░░░░░░░░░░░░    ░░░░░░░░██\e[0m        █
█        \033[1;35m\e[1;46m██▓▓▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░██\e[0m        █
█        \033[1;35m\e[1;46m██▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░██\e[0m        █
█        \033[1;35m\e[1;46m██▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░██\e[0m        █
█        \033[1;35m\e[1;46m██▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░██\e[0m        █
█          \033[1;35m\e[1;46m▓▓▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░██\e[0m          █
█          \033[1;35m\e[1;46m██▓▓▓▓▓▓▒▒▒▒▒▒▒▒░░░░░░░░░░▒▒▒▒██\e[0m          █
█          \033[1;35m░░\e[1;46m▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\e[0m\033[1;35m░░ \e[0m         █
█            \033[1;35m░░\e[1;46m▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒██\e[0m\033[1;35m░░\e[0m            █
█              \033[1;35m░░\e[1;46m██▓▓▓▓▓▓▓▓▓▓▓▓▓▓████\e[0m\033[1;35m░░\e[0m              █
█                 \033[1;35m░░░░\e[1;46m████████████\e[0m\033[1;35m░░\e[0m                 █
█                     \033[1;35m░░░░░░░░░░░░\033[0m\e[0m                   █
█           \033[0;35m\e[5m__  __ _       _ _____ _______ \e[0m          █
██         \033[0;35m\e[5m|  \/  (_)     (_)  __ \__   __|\e[0m         ██
██         \033[0;35m\e[5m| \  / |_ _ __  _| |__) | | |\e[0m            ██
██         \033[0;35m\e[5m| |\/| | | '_ \| |  _  /  | |\e[0m            ██
██        \033[0;35m\e[5m | |  | | | | | | | | \ \  | |\e[0m            ██
██         \033[0;35m\e[5m|_|  |_|_|_| |_|_|_|  \_\ |_|\033[0m\e[0m            ██
███                                                ███
███                                                ███
████  With love by ❤️\e[0m \033[1;36m\e[4m\e]8;;https://github.com/GreenPG\aGpasquet\e]8;;\a\e[24m\033[0m❤️\e[0m  and ❤️\e[0m \e[38;5;201m\e[4m\e]8;;https://github.com/TheEmperorPenguin\aGtouzali\e]8;;\a\e[24m\033[0m❤️\e[0m   ████
██████████████████████████████████████████████████████
endef
export HEADER

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

%.o: %.c 
	@$(CC) $(CFLAGS) -o ./obj/$@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(addprefix ./obj/,$(OBJS)) $(LIBS) $(HEADERS) -o $(NAME)
	@clear
	@echo "$$HEADER"

clean:
	@rm -f $(addprefix ./obj/,$(OBJS))
	@rm -rf $(LIBMLX)/build
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx

-include bonus.mk
-include test.mk
