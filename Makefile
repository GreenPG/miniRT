NAME	= miniRT

CFLAGS	= -Wextra -Wall -Werror

LIBMLX	= ./lib/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include

LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	:= main.c

OBJS	:= ${SRCS:.c=.o}

CC	:= cc

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o ./obj/$@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) ./obj/$(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
