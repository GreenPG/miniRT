NAME	=	miniRT

CFLAGS	=	-Wextra -Wall -Werror -g

LIBMLX	=	./lib/MLX42

LIBFT	=	./lib/libft

HEADERS	=	-I ./includes -I $(LIBMLX)/include -I $(LIBFT)/include

LIBS	= 	$(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	=	main.c	\
			utils.c \
			parsing.c \
			structs_utils.c \
			parsing_utils.c \
			camera.c \
			ambiant_light.c \
			light.c \
			sphere.c 	\
			color.c	\
			vector.c \
			plane.c	\
			cylinder.c

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

%.o: ./src/%.c
	@$(CC) $(CFLAGS) -o ./obj/$@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(addprefix ./obj/,$(OBJS)) $(LIBS) $(HEADERS) -o $(NAME)
	# @clear
	@echo "$$HEADER"

clean:
	@rm -f $(addprefix ./obj/,$(OBJS))
	@rm -rf $(LIBMLX)/build
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx

-include test.mk
