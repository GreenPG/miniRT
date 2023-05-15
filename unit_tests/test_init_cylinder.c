/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:20:40 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/15 10:08:06 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"

TEST	ASSERT_VECTOR_EQ(t_vector *actual, t_vector *expected)
{
	ASSERT_EQ_FMT(expected->x, actual->x, "%f");
	ASSERT_EQ_FMT(expected->y, actual->y, "%f");
	ASSERT_EQ_FMT(expected->z, actual->z, "%f");
	PASS();
}

TEST	ASSERT_CYLINDER_EQ(t_cylinder *actual, t_cylinder *expected)
{
	CHECK_CALL(ASSERT_VECTOR_EQ(actual->origin, expected->origin));
	CHECK_CALL(ASSERT_VECTOR_EQ(actual->direction, expected->direction));
	ASSERT_EQ_FMT(expected->diameter, actual->diameter, "%f");
	ASSERT_EQ_FMT(expected->height, actual->height, "%f");
	ASSERT_EQ_FMT(expected->color, actual->color, "%i");
	PASS();
}

TEST	correct_input(void) {
	t_cylinder *cyl1 = init_cylinder("cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255");
	t_cylinder *expected = malloc(sizeof(t_cylinder));
	expected->origin = init_vector("50.0,0.0,20.6");
	expected->direction = init_vector("0.0,0.0,1.0");
	expected->diameter = 14.2;
	expected->height = 21.42;
	expected->color = get_rgba(10, 0, 255, 255);

	CHECK_CALL(ASSERT_CYLINDER_EQ(cyl1, expected));
	free_cylinder(&cyl1);
	free_cylinder(&expected);
	PASS();
}

TEST	wrong_vector(void) {
	t_cylinder *cyl1 = init_cylinder("cy 5a0.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255");
	t_cylinder *cyl2 = init_cylinder("cy 50.0,--0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255");
	t_cylinder *cyl3 = init_cylinder("cy 50.0,0.0,+-2fd0.6 0.0,0.0,1.0 14.2 21.42 10,0,255");
	t_cylinder *cyl4 = init_cylinder("cy 50.0,0.0,20.6 10.0,0.0,1.0 14.2 21.42 10,0,255");
	t_cylinder *cyl5 = init_cylinder("cy 50.0,0.0,20.6 0.0,0fd.df0,1.0 14.2 21.42 10,0,255");
	t_cylinder *cyl6 = init_cylinder("cy 50.0,0.0,20.6 0.0,0.0,-1.10 14.2 21.42 10,0,255");

	ASSERT_EQ_FMT(NULL, cyl1, "%p");
	ASSERT_EQ_FMT(NULL, cyl2, "%p");
	ASSERT_EQ_FMT(NULL, cyl3, "%p");
	ASSERT_EQ_FMT(NULL, cyl4, "%p");
	ASSERT_EQ_FMT(NULL, cyl5, "%p");
	ASSERT_EQ_FMT(NULL, cyl6, "%p");
	PASS();
}

TEST	wrong_diameter(void) {
	t_cylinder *cyl1 = init_cylinder("cy 50.0,0.0,20.6 0.0,0.0,1.0 -14.2 21.42 10,0,255");
	t_cylinder *cyl2 = init_cylinder("cy 50.0,0.0,20.6 0.0,0.0,1.0 1fd4.2 21.42 10,0,255");

	ASSERT_EQ_FMT(NULL, cyl1, "%p");
	ASSERT_EQ_FMT(NULL, cyl2, "%p");
	PASS();
}

TEST	wrong_height(void) {
	t_cylinder *cyl1 = init_cylinder("cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 -21.42 10,0,255");
	t_cylinder *cyl2 = init_cylinder("cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 2gfd1gf.42 10,0,255");

	ASSERT_EQ_FMT(NULL, cyl1, "%p");
	ASSERT_EQ_FMT(NULL, cyl2, "%p");
	PASS();
}

TEST	wrong_color(void) {
	t_cylinder *cyl1 = init_cylinder("cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 -10,0,255");
	t_cylinder *cyl2 = init_cylinder("cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,fds0,255");
	t_cylinder *cyl3 = init_cylinder("cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,259");

	ASSERT_EQ_FMT(NULL, cyl1, "%p");
	ASSERT_EQ_FMT(NULL, cyl2, "%p");
	ASSERT_EQ_FMT(NULL, cyl3, "%p");
	PASS();
}

SUITE(test_init_cylinder) {
	RUN_TEST(correct_input);
	RUN_TEST(wrong_vector);
	RUN_TEST(wrong_diameter);
	RUN_TEST(wrong_height);
	RUN_TEST(wrong_color);
}
