/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:00:37 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/14 15:04:39 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"

extern	SUITE(check_path_suite);
extern	SUITE(test_init_coords);
extern	SUITE(test_init_vector);
extern	SUITE(test_init_color);

GREATEST_MAIN_DEFS();

int	main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(check_path_suite);
	RUN_SUITE(test_init_coords);
	RUN_SUITE(test_init_vector);
	RUN_SUITE(test_init_color);
	GREATEST_MAIN_END();
}
