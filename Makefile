NAME	= miniRT

CFLAGS	= -Wextra -Wall -Werror

LIBMLX	= ./lib/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include

LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	:= main.c

OBJS	:= ${SRCS:.c=.o}

CC	:= cc

info: header

define HEADER

                    \033[1;35m\e[1;46m▓▓▓▓▓▓▓▓▓▓▓▓\e[0m
              \033[1;35m░░\e[1;46m████░░░░░░░░░░░░████\e[0m
            \033[1;35m░░\e[1;46m██▒▒░░░░░░░░░░░░░░░░░░██\e[0m
          \033[1;35m░░\e[1;46m██▒▒▒▒░░░░░░░░░░░░░░░░░░░░██\e[0m
         \033[1;35m\e[1;46m██▒▒▒▒░░░░░░░░░░░░░░    ░░░░░░██\e[0m
         \033[1;35m\e[1;46m██▒▒▒▒░░░░░░░░░░░░        ░░░░██\e[0m
       \033[1;35m\e[1;46m██▓▓▒▒▒▒░░░░░░░░░░░░        ░░░░░░██\e[0m
       \033[1;35m\e[1;46m██▓▓▒▒▒▒░░░░░░░░░░░░░░    ░░░░░░░░██\e[0m
       \033[1;35m\e[1;46m██▓▓▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░██\e[0m
       \033[1;35m\e[1;46m██▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░██\e[0m
       \033[1;35m\e[1;46m██▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░██\e[0m
       \033[1;35m\e[1;46m██▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░██\e[0m
         \033[1;35m\e[1;46m▓▓▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░██\e[0m
         \033[1;35m\e[1;46m██▓▓▓▓▓▓▒▒▒▒▒▒▒▒░░░░░░░░░░▒▒▒▒██\e[0m
         \033[1;35m░░\e[1;46m▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██\e[0m\033[1;35m░░
           \033[1;35m░░\e[1;46m▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒██\e[0m\033[1;35m░░
             \033[1;35m░░\e[1;46m██▓▓▓▓▓▓▓▓▓▓▓▓▓▓████\e[0m\033[1;35m░░
                \033[1;35m░░░░\e[1;46m████████████\e[0m\033[1;35m░░
                   ░░░░░░░░░░░░\033[0;35m\e[5m
          __  __ _       _ _____ _______ 
         |  \/  (_)     (_)  __ \__   __|
         | \  / |_ _ __  _| |__) | | |
         | |\/| | | '_ \| |  _  /  | |   
         | |  | | | | | | | | \ \  | |
         |_|  |_|_|_| |_|_|_|  \_\ |_|\033[0m\e[0m
    
   With love by ❤️\e[0m \033[1;36m\e[4mGpasquet\e[24m\033[0m❤️\e[0m  and ❤️\e[0m \e[38;5;201m\e[4mGtouzali\e[24m\033[0m❤️\e[0m
endef
export HEADER

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: ./src/%.c
	@$(CC) $(CFLAGS) -o ./obj/$@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@clear
	@echo "$$HEADER"
	@$(CC) ./obj/$(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
