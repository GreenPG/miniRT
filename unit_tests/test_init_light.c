/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:52:09 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 16:27:16 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"

TEST	ASSERT_COORDS_EQ(t_coords *actual, t_coords *expected)
{
	ASSERT_EQ_FMT(expected->x, actual->x, "%f");
	ASSERT_EQ_FMT(expected->y, actual->y, "%f");
	ASSERT_EQ_FMT(expected->z, actual->z, "%f");
	PASS();
}

TEST	ASSERT_LIGHT_EQ(t_light *actual, t_light *expected)
{
	ASSERT_EQ_FMT(expected->brightness, actual->brightness, "%f");
	ASSERT_EQ_FMT(expected->colors, actual->colors, "%i");
	ASSERT_COORDS_EQ(actual->pos, expected->pos);
	PASS();
}

TEST	correct_input(void) {
	t_light	*light1 = init_light("L -40.0,50.0,0.0 0.6 10,0,255");
	t_light	*expected = malloc(sizeof(t_light));
	expected->pos = init_coords(-40.0, 50.0, 0.0);
	expected->brightness = 0.6;
	expected->colors = get_rgba(10, 0, 255, 255);

	CHECK_CALL(ASSERT_LIGHT_EQ(light1, expected));
	PASS();
}

TEST	wrong_pos(void) {
	t_light	*light1 = init_light("L -4a0.0,50.0,0.0 0.6 10,0,255");
	t_light	*light2 = init_light("L --40.0,50.0,0.0 0.6 10,0,255");
	t_light	*light3 = init_light("L -40.0,50f.0,0.0 0.6 10,0,255");

	ASSERT_EQ_FMT(NULL, light1, "%p");
	ASSERT_EQ_FMT(NULL, light2, "%p");
	ASSERT_EQ_FMT(NULL, light3, "%p");
	PASS();
}

TEST	wrong_brightness(void) {
	t_light	*light1 = init_light("L -40.0,50.0,0.0 -0.6 10,0,255");
	t_light	*light2 = init_light("L -40.0,50.0,0.0 1.6 10,0,255");
	t_light	*light3 = init_light("L -40.0,50.0,0.0 0a.6 10,0,255");

	ASSERT_EQ_FMT(NULL, light1, "%p");
	ASSERT_EQ_FMT(NULL, light2, "%p");
	ASSERT_EQ_FMT(NULL, light3, "%p");

	PASS();
}

TEST	wrong_colors(void) {
	t_light	*light1 = init_light("L -40.0,50.0,0.0 0.6 -10,0,255");
	t_light	*light2 = init_light("L -40.0,50.0,0.0 0.6 10,0.32,255");
	t_light	*light3 = init_light("L -40.0,50.0,0.0 0.6 10,0,259");
	t_light	*light4 = init_light("L -40.0,50.0,0.0 0.6 10,0aa,255");

	ASSERT_EQ_FMT(NULL, light1, "%p");
	ASSERT_EQ_FMT(NULL, light2, "%p");
	ASSERT_EQ_FMT(NULL, light3, "%p");
	ASSERT_EQ_FMT(NULL, light4, "%p");

	PASS();
}

SUITE(test_init_light) {
	RUN_TEST(correct_input);
	RUN_TEST(wrong_pos);
	RUN_TEST(wrong_brightness);
	RUN_TEST(wrong_colors);
}
