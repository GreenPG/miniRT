# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                  +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 13:38:40 by gpasquet          #+#    #+#              #
#    Updated: 2022/12/16 10:54:21 by gpasquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	clang	

NAME	= 	libft.a

CFLAGS	= 	-Wall -Wextra -Werror

SRCS	=	./src/string/ft_split.c	\
			./src/string/ft_strdup.c		\
			./src/string/ft_strrchr.c		\
			./src/string/ft_strncmp.c		\
			./src/string/ft_striteri.c		\
			./src/string/ft_strtrim.c		\
			./src/string/ft_strmapi.c		\
			./src/string/ft_strchr.c		\
			./src/string/ft_strlcat.c		\
			./src/string/ft_strlcpy.c		\
			./src/string/ft_strjoin.c		\
			./src/string/ft_substr.c		\
			./src/string/ft_strnstr.c		\
			./src/string/ft_strlen.c		\
			./src/memory/ft_memchr.c		\
			./src/memory/ft_calloc.c		\
			./src/memory/ft_memmove.c		\
			./src/memory/ft_memcmp.c		\
			./src/memory/ft_bzero.c			\
			./src/memory/ft_memset.c		\
			./src/memory/ft_memcpy.c		\
			./src/conversion/ft_atoi.c 		\
			./src/conversion/ft_atoll.c 		\
			./src/conversion/ft_itoa.c		\
			./src/char/ft_isalnum.c		\
			./src/char/ft_isdigit.c		\
			./src/char/ft_isalpha.c		\
			./src/char/ft_toupper.c		\
			./src/char/ft_isascii.c		\
			./src/char/ft_tolower.c		\
			./src/char/ft_isprint.c		\
			./src/list/ft_lstnew.c		\
 			./src/list/ft_lstadd_front.c\
			./src/list/ft_lstsize.c		\
			./src/list/ft_lstlast.c		\
			./src/list/ft_lstadd_back.c	\
			./src/list/ft_lstdelone.c	\
			./src/list/ft_lstclear.c	\
			./src/list/ft_lstiter.c		\
			./src/list/ft_lstmap.c		\
			./src/print/ft_putstr_fd.c	\
			./src/print/ft_putchar_fd.c	\
			./src/print/ft_putendl_fd.c	\
			./src/print/ft_putnbr_fd.c	\
			./src/print/ft_puthexa.c	\
			./src/print/ft_putptr.c		\
			./src/print/ft_printf.c		\
			./src/gnl/get_next_line.c	\
			./src/gnl/get_next_line_utils.c	
			
OBJS= 	${SRCS:%.c=%.o}

RM		=	rm -f

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	$(NAME)
	
clean:	
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: 
	all clean fclean re
