# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 11:03:28 by gpasquet          #+#    #+#              #
#    Updated: 2023/06/12 11:03:40 by gpasquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##########################	FILES	############################################

TSRCS =  unit_tests/runner.c \
		unit_tests/test_init_triangle.c# $(shell find unit_tests -name '*.c')

TRUNNER =	run_tests

TOBJS =	$(TSRCS:%.c=%.o)

BOBJS = $(addprefix ./obj/, $(OBJS_BONUS))

##########################	CMDS	############################################

VALGRIND :=	valgrind \
									--quiet					\
									--leak-check=full		\
									--show-leak-kinds=all	\
									--error-exitcode=1 	\

test: test.build
	./run_tests

test.build: bonus
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

$(TRUNNER):	BOBJS	:=	$(filter-out %/main_bonus.o, $(BOBJS))

$(TRUNNER): $(OBJS) $(TOBJS)
	$(CC) $(CFLAGS) $(HEADERS_BONUS) $(BOBJS) $(TOBJS) $(LIBS) -o $(TRUNNER)

$(TOBJS): %.o: %.c
	$(CC) $(CFLAGS) $(HEADERS_BONUS) -c $< -o $@
