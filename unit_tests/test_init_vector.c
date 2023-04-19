/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:33:10 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 15:31:53 by gpasquet         ###   ########.fr       */
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

TEST	correct_input(void) 
{
	t_vector	*actual1 = init_vector("0.0,0.0,0.0 0.0,1.0,0.0");
	t_vector	*actual2 = init_vector("50.0,0.0,20.6 0.0,0.0,1.0");

	t_vector	*expected = malloc(sizeof(t_vector));
	expected->x_o = 0.0;
	expected->y_o = 0.0;
	expected->z_o = 0.0;
	expected->x_d = 0.0;
	expected->y_d = 1.0;
	expected->z_d = 0.0;

	ASSERT_VECTOR_EQ(actual1, expected);
	expected->x_o = 50.0;
	expected->y_o = 0.0;
	expected->z_o = 20.6;
	expected->x_d = 0.0;
	expected->y_d = 0.0;
	expected->z_d = 1.0;
	
	ASSERT_VECTOR_EQ(actual2, expected);
	free(actual1);
	free(actual2);
	free(expected);
	PASS();
}

SUITE(test_init_vector)
{
	RUN_TEST(correct_input);
}
