/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:55:46 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/20 15:31:30 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"

TEST	ASSERT_SPHERE_EQ(t_sphere *actual, t_sphere *expected)
{
	ASSERT_EQ_FMT(expected->pos->x, actual->pos->x, "%f");
	ASSERT_EQ_FMT(expected->pos->y, actual->pos->y, "%f");
	ASSERT_EQ_FMT(expected->pos->z, actual->pos->z, "%f");
	ASSERT_EQ_FMT(expected->diameter, actual->diameter, "%f");
	ASSERT_EQ_FMT(expected->color, actual->color, "%i");
	PASS();
}

TEST	correct_input(void)
{
	t_sphere	*sphere = init_sphere("sp 0.0,0.0,20.6 12.6 10,0,255");
	t_sphere	*expected = malloc(sizeof(t_sphere));
	expected->diameter = 12.6;
	expected->pos = init_coords(0.0, 0.0, 20.6);
	expected->color = get_rgba(10,0,255, 255);

	ASSERT_SPHERE_EQ(sphere, expected);
	free_sphere(&sphere);
	free_sphere(&expected);
	PASS();
}

TEST	wrong_pos(void)
{
	t_sphere	*sphere1 = init_sphere("sp 0.a0,0.0,20.6 12.6 10,0,255");
	t_sphere	*sphere2 = init_sphere("sp 0.0,0dsa.0,20.6 12.6 10,0,255");
	t_sphere	*sphere3 = init_sphere("sp 0.0,0.0,.6 12.6 10,0,255");

	ASSERT_EQ_FMT(NULL, sphere1, "%p");
	ASSERT_EQ_FMT(NULL, sphere2, "%p");
	ASSERT_EQ_FMT(NULL, sphere3, "%p");
	PASS();
}

TEST	wrong_diameter(void)
{
	t_sphere	*sphere1 = init_sphere("sp 0.0,0.0,20.6 -12.6 10,0,255");
	t_sphere	*sphere2 = init_sphere("sp 0.0,0.0,20.6 1dsa2.6 10,0,255");
	t_sphere	*sphere3 = init_sphere("sp 0.0,0.0,20.6 0 10,0,255");

	ASSERT_EQ_FMT(NULL, sphere1, "%p");
	ASSERT_EQ_FMT(NULL, sphere2, "%p");
	ASSERT_EQ_FMT(NULL, sphere3, "%p");
	PASS();
}

TEST	wrong_color(void)
{
	t_sphere	*sphere1 = init_sphere("sp 0.0,0.0,20.6 12.6 1a0,0,255");
	t_sphere	*sphere2 = init_sphere("sp 0.0,0.0,20.6 12.6 10,0,-255");
	t_sphere	*sphere3 = init_sphere("sp 0.0,0.0,20.6 12.6 10,0,2521");

	ASSERT_EQ_FMT(NULL, sphere1, "%p");
	ASSERT_EQ_FMT(NULL, sphere2, "%p");
	ASSERT_EQ_FMT(NULL, sphere3, "%p");
	PASS();
}

SUITE(test_init_sphere)
{
	RUN_TEST(correct_input);
	RUN_TEST(wrong_pos);
	RUN_TEST(wrong_diameter);
	RUN_TEST(wrong_color);
}
