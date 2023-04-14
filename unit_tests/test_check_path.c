/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:15:17 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/14 11:05:07 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"

TEST	correct_input(void) {

	ASSERT_EQ_FMT(0, check_path("test.rt"), "%i");
	ASSERT_EQ_FMT(0, check_path("t.rt"), "%i");
	ASSERT_EQ_FMT(0, check_path("very_looooooooooooooooooooooooooooooooooooooog_test.rt"), "%i");
	PASS();
}

TEST	wrong_extension(void){

	ASSERT_EQ_FMT(1, check_path("test.txt"), "%i");
	ASSERT_EQ_FMT(1, check_path("test.aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), "%i");
	ASSERT_EQ_FMT(1, check_path("test.a"), "%i");
	PASS();
}

TEST	no_extension(void) {

	ASSERT_EQ_FMT(1, check_path("test"), "%i");
	PASS();
}

SUITE(check_path_suite) {
	RUN_TEST(correct_input);
	RUN_TEST(wrong_extension);
	RUN_TEST(no_extension);
}
