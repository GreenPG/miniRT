/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:52:40 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/14 15:12:20 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"

TEST	ASSERT_COLOR_EQ(t_color *actual, t_color *expected)
{
	ASSERT_EQ_FMT(expected->r, actual->r, "%i");
	ASSERT_EQ_FMT(expected->g, actual->g, "%i");
	ASSERT_EQ_FMT(expected->b, actual->b, "%i");
	PASS();
}

TEST	correct_input(void)
{
	t_color	*color1	 = init_color(0, 0, 0);
	t_color *color2	= init_color(214, 121, 20);
	t_color	*expected = malloc(sizeof(t_color));
	expected->r = 0;
	expected->g = 0;
	expected->b = 0;

	ASSERT_COLOR_EQ(color1, expected);
	
	expected->r = 214;
	expected->g = 121;
	expected->b = 20;
	ASSERT_COLOR_EQ(color2, expected);
	
	free(color1);
	free(color2);
	free(expected);
	PASS();
}

TEST	negative_input(void)
{
	t_color	*color1 = init_color(-1, 0, 0);
	t_color	*color2 = init_color(0, -1,  0);
	t_color	*color3 = init_color(0, 0, -1);

	ASSERT_EQ_FMT(NULL, color1, "%p");
	ASSERT_EQ_FMT(NULL, color2, "%p");
	ASSERT_EQ_FMT(NULL, color3, "%p");
	free(color1);
	free(color2);
	free(color3);
	PASS();
}

TEST	too_big_input(void)
{
	t_color	*color1 = init_color(256, 0, 0);
	t_color	*color2 = init_color(0, 256,  0);
	t_color	*color3 = init_color(0, 0, 2222222222);

	ASSERT_EQ_FMT(NULL, color1, "%p");
	ASSERT_EQ_FMT(NULL, color2, "%p");
	ASSERT_EQ_FMT(NULL, color3, "%p");
	free(color1);
	free(color2);
	free(color3);
	PASS();
}

SUITE(test_init_color)
{
	RUN_TEST(correct_input);
	RUN_TEST(negative_input);
	RUN_TEST(too_big_input);
}
