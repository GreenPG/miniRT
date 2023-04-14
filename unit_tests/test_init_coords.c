/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_coords.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:43:43 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/14 14:36:56 by gpasquet         ###   ########.fr       */
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

TEST	correct_input(void) 
{
	t_coords	*actual1 = init_coords(0.0, 0.0, 0.0);
	t_coords	*actual2 = init_coords(10.0, -50.0, 2.5);

	t_coords	*expected = malloc(sizeof(t_coords));
	expected->x = 0.0;
	expected->y = 0.0;
	expected->z = 0.0;

	ASSERT_COORDS_EQ(actual1, expected);
	
	expected->x = 10.0;
	expected->y = -50.0;
	expected->z = 2.5;
	ASSERT_COORDS_EQ(actual2, expected);
	free(actual1);
	free(actual2);
	free(expected);
	PASS();
}

SUITE(test_init_coords)
{
	RUN_TEST(correct_input);
}
