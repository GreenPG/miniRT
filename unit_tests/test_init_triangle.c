/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:57:37 by gpasquet          #+#    #+#             */
/*   Updated: 2023/06/12 11:01:53 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../bonus/includes/minirt_bonus.h"

TEST	ASSERT_VECTOR_EQ(t_vector *actual, t_vector *expected)
{
	ASSERT_EQ_FMT(expected->x, actual->x, "%f");
	ASSERT_EQ_FMT(expected->y, actual->y, "%f");
	ASSERT_EQ_FMT(expected->z, actual->z, "%f");
	PASS();
}

TEST	ASSERT_TRIANGLE_EQ(t_triangle *actual, t_triangle *expected)
{
	CHECK_CALL(ASSERT_VECTOR_EQ(actual->a, expected->a));
	CHECK_CALL(ASSERT_VECTOR_EQ(actual->b, expected->b));
	CHECK_CALL(ASSERT_VECTOR_EQ(actual->c, expected->c));
	CHECK_CALL(ASSERT_VECTOR_EQ(actual->normal, expected->normal));
	ASSERT_EQ_FMT(expected->color, actual->color, "%i");
	PASS();
}

TEST	correct_input(void) {
	t_triangle	*triangle = init_triangle("tr 0,0,0 1,0,0 0,1,0 255,255,255");
	t_triangle	*expected = malloc(sizeof(t_triangle));
	expected->a = init_vector("0,0,0");
	expected->b = init_vector("1,0,0");
	expected->c = init_vector("0,1,0");
	expected->normal = init_vector("0,0,1");
	expected->color = get_rgba(255,255,255,255);

	CHECK_CALL(ASSERT_TRIANGLE_EQ(triangle, expected));
	free_triangle(&triangle);
	free_triangle(&expected);
	PASS();
}

TEST	wrong_coords(void) {
	t_triangle	*triangle1 = init_triangle("tr 0,a,0 1,0,0 0,1,0 255,255,255");
	t_triangle	*triangle2 = init_triangle("tr 0,0,0 1,0.23.2,0 0,1,0 255,255,255");
	t_triangle	*triangle3 = init_triangle("tr 0,0,0 1,0,0 0,1 255,255,255");
	t_triangle	*triangle4 = init_triangle("tr 000 1,0,0 0,1,0 255,255,255");

	ASSERT_EQ_FMT(NULL, triangle1, "%p");
	ASSERT_EQ_FMT(NULL, triangle2, "%p");
	ASSERT_EQ_FMT(NULL, triangle3, "%p");
	ASSERT_EQ_FMT(NULL, triangle4, "%p");
	PASS();
}

TEST	wrong_colors(void) {
	t_triangle	*triangle1 = init_triangle("tr 0,1,0 1,0,0 0,1,0 255,255");
	t_triangle	*triangle2 = init_triangle("tr 0,1,0 1,0,0 0,1,0 255,255,2555555555555");
	t_triangle	*triangle3 = init_triangle("tr 0,1,0 1,0,0 0,1,0 255,-55,255");
	t_triangle	*triangle4 = init_triangle("tr 0,0,0 1,0,0 0,1,0 2ss55,255,255");

	ASSERT_EQ_FMT(NULL, triangle1, "%p");
	ASSERT_EQ_FMT(NULL, triangle2, "%p");
	ASSERT_EQ_FMT(NULL, triangle3, "%p");
	ASSERT_EQ_FMT(NULL, triangle4, "%p");
	PASS();
}

SUITE(test_init_triangle) {
	RUN_TEST(correct_input);
	RUN_TEST(wrong_coords);
	RUN_TEST(wrong_colors);
}
