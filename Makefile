NAME	=	miniRT

CFLAGS	=	-Wextra -Wall -Werror

LIBMLX	=	./lib/MLX42

HEADERS	=	-I ./includes -I $(LIBMLX)/include

LIBS	=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	=	main.c		\
			utils.c		\
			parsing.c	\
			camera.c	\
			colors.c	\
			vector.c

OBJS	= ${SRCS:.c=.o}

CC	:= cc

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

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: ./src/%.c
	@$(CC) $(CFLAGS) -o ./obj/$@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(addprefix ./obj/,$(OBJS)) $(LIBS) $(HEADERS) -o $(NAME)
	@clear
	@echo "$$HEADER"

clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
