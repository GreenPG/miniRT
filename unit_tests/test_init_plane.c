/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:01:20 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 18:08:04 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"

TEST	ASSERT_VECTOR_EQ(t_vector *actual, t_vector *expected)
{
	ASSERT_EQ_FMT(expected->x_o, actual->x_o, "%f");
	ASSERT_EQ_FMT(expected->y_o, actual->y_o, "%f");
	ASSERT_EQ_FMT(expected->z_o, actual->z_o, "%f");
	ASSERT_EQ_FMT(expected->x_d, actual->x_d, "%f");
	ASSERT_EQ_FMT(expected->y_d, actual->y_d, "%f");
	ASSERT_EQ_FMT(expected->z_d, actual->z_d, "%f");
	PASS();
}

TEST	ASSERT_PLANE_EQ(t_plane *actual, t_plane *expected)
{
	CHECK_CALL(ASSERT_VECTOR_EQ(actual->vector, expected->vector));
	ASSERT_EQ_FMT(expected->colors, actual->colors, "%i");
	PASS();
}

TEST	correct_input(void) {
	t_plane	*plane1	= init_plane("pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,255");
	t_plane expected;
	expected.vector = init_vector("0.0,0.0,-10.0 0.0,1.0,0.0");
	expected.colors = get_rgba(0, 0, 255, 255);

	CHECK_CALL(ASSERT_PLANE_EQ(plane1, &expected));
	PASS();
}

TEST	wrong_vector(void) {
	t_plane	*plane1	= init_plane("pl 0i.0,0.0,-10.0 0.0,1.0,0.0 0,0,255");
	t_plane	*plane2	= init_plane("pl 0.0,0.0,-+10.0 0.0,1.0,0.0 0,0,255");
	t_plane	*plane3	= init_plane("pl 0.0,0.0,-10.0 2.0,1.0,0.0 0,0,255");
	t_plane	*plane4	= init_plane("pl 0.0,0.0,-10.0 0.0,-1.1,0.0 0,0,255");
	t_plane	*plane5	= init_plane("pl 0.0,0.0,-10.0 0.0,1.0,0.s0 0,0,255");

	ASSERT_EQ_FMT(NULL, plane1, "%p");
	ASSERT_EQ_FMT(NULL, plane2, "%p");
	ASSERT_EQ_FMT(NULL, plane3, "%p");
	ASSERT_EQ_FMT(NULL, plane4, "%p");
	ASSERT_EQ_FMT(NULL, plane5, "%p");
	PASS();
}

TEST	wrong_colors(void) {
	t_plane	*plane1	= init_plane("pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,259");
	t_plane	*plane2	= init_plane("pl 0.0,0.0,-10.0 0.0,1.0,0.0 -1,0,255");
	t_plane	*plane3	= init_plane("pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,fds,255");

	ASSERT_EQ_FMT(NULL, plane1, "%p");
	ASSERT_EQ_FMT(NULL, plane2, "%p");
	ASSERT_EQ_FMT(NULL, plane3, "%p");
	PASS();

}

SUITE(test_init_plane)
{
	RUN_TEST(correct_input);
	RUN_TEST(wrong_vector);
	RUN_TEST(wrong_colors);
}
