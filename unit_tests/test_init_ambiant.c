/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_ambiant.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:25:15 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/20 15:21:56 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"
#include <math.h>

TEST	ASSERT_AMB_L_EQ(t_ambiant_l	*actual, t_ambiant_l *expected)
{
	ASSERT_EQ_FMT(expected->light_ratio, actual->light_ratio, "%f");
	ASSERT_EQ_FMT(expected->colors, actual->colors, "%i");
	PASS();
}

TEST	correct_input(void) {	
	t_ambiant_l	*amb_l1 = init_ambiant_l("A 0.2 255,255,255");

	t_ambiant_l	*expected = malloc(sizeof(t_ambiant_l));
	expected->light_ratio = 0.2;
	expected->colors = get_rgba(255, 255, 255, 255);

	ASSERT_AMB_L_EQ(amb_l1, expected);
	free(amb_l1);
	free(expected);
	PASS();
}

TEST	wrong_light(void) {
	t_ambiant_l	*amb_l1 = init_ambiant_l("A -0.2 255,255,255"); 
	t_ambiant_l	*amb_l2 = init_ambiant_l("A 1.2 255,255,255"); 
	t_ambiant_l	*amb_l3 = init_ambiant_l("A -a0.2 255,255,255"); 

	ASSERT_EQ_FMT(NULL, amb_l1, "%p");
	ASSERT_EQ_FMT(NULL, amb_l2, "%p");
	ASSERT_EQ_FMT(NULL, amb_l3, "%p");
	PASS();
}

TEST	wrong_colors(void) {
	t_ambiant_l	*amb_l1 = init_ambiant_l("A 0.2 255,265,255"); 
	t_ambiant_l	*amb_l2 = init_ambiant_l("A 0.2 -20,255,255"); 
	t_ambiant_l	*amb_l3 = init_ambiant_l("A -0.2 255,255,25312325"); 

	ASSERT_EQ_FMT(NULL, amb_l1, "%p");
	ASSERT_EQ_FMT(NULL, amb_l2, "%p");
	ASSERT_EQ_FMT(NULL, amb_l3, "%p");
	PASS();
}

SUITE(test_init_ambiant)
{
	RUN_TEST(correct_input);
	RUN_TEST(wrong_light);
	RUN_TEST(wrong_colors);
}
