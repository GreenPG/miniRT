/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:33:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/17 15:08:26 by gpasquet         ###   ########.fr       */
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

TEST	correct_input(void) 
{
	t_vector	*actual1 = init_vector("0.0,0.0,0.0");
	t_vector	*actual2 = init_vector("50.0,0.0,20.6");
	t_vector	*actual3 = init_vector("0.0,0.0,-1.0");

	t_vector	*expected = malloc(sizeof(t_vector));
	expected->x = 0.0;
	expected->y = 0.0;
	expected->z = 0.0;

	ASSERT_VECTOR_EQ(actual1, expected);
	expected->x = 50.0;
	expected->y = 0.0;
	expected->z = 20.6;
	
	ASSERT_VECTOR_EQ(actual2, expected);
	expected->x = 0.0;
	expected->y = 0.0;
	expected->z = -1.0;

	ASSERT_VECTOR_EQ(actual3, expected);
	free(actual1);
	free(actual2);
	free(actual3);
	free(expected);
	PASS();
}

SUITE(test_init_vector)
{
	RUN_TEST(correct_input);
}
