# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 11:03:28 by gpasquet          #+#    #+#              #
#    Updated: 2023/04/14 12:16:10 by gpasquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##########################	FILES	############################################

TSRCS = $(shell find unit_tests -name '*.c')

TRUNNER =	run_tests

TOBJS =	$(TSRCS:%.c=%.o)

BOBJS = $(addprefix ./obj/, $(OBJS))

##########################	CMDS	############################################

VALGRIND :=	valgrind \
									--quiet					\
									--leak-check=full		\
									--show-leak-kinds=all	\
									--error-exitcode=1 	\

test: test.build
	./run_tests

test.build:
	$(MAKE) -s --jobs=8 $(TRUNNER)

test.leak: test.build
	$(VALGRIND) ./run_tests

test.clean:
	@n=1; \
	for file in $(TOBJS); do \
		if test -e $$file; then \
			if [ $$n -eq 1 ]; then \
				printf "Cleaning test .o files \n"; \
			fi; \
			n=$$((n + 1)); \
			rm $$file; \
		fi \
	done
	@rm -rf $(NAME)
	@rm -rf $(TRUNNER)

fclean: test.clean

test.re: test.clean test

.PHONY:	test test.build test.clean test.re

$(TRUNNER):	BOBJS	:=	$(filter-out %/main.o, $(BOBJS))

$(TRUNNER): $(OBJS) $(TOBJS)
	$(CC) $(CFLAGS) $(HEADERS) $(BOBJS) $(TOBJS) $(LIBS) -o $(TRUNNER)

$(TOBJS): %.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
