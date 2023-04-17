/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_atof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:40:15 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/17 10:44:39 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"

TEST	correct_input(void) {
	ASSERT_EQ_FMT(10.0, ft_atof("10.0"), "%f");
	ASSERT_EQ_FMT(10.12354, ft_atof("10.12354"), "%f");
	ASSERT_EQ_FMT(-10.2, ft_atof("-10.2"), "%f");
	ASSERT_EQ_FMT(10.0, ft_atof("10.0"), "%f");

	PASS();
}

SUITE(test_atof) {
	RUN_TEST(correct_input);
}
