/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:00:37 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/15 10:10:24 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"

extern	SUITE(check_path_suite);
extern	SUITE(test_init_vector);
extern	SUITE(test_atof);
extern	SUITE(test_init_ambiant);
extern	SUITE(test_init_camera);
extern	SUITE(test_init_sphere);
extern	SUITE(test_init_light);
extern	SUITE(test_init_plane);
extern	SUITE(test_init_cylinder);
extern	SUITE(test_parsing);

GREATEST_MAIN_DEFS();

int	main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(check_path_suite);
	RUN_SUITE(test_init_vector);
	RUN_SUITE(test_atof);
	RUN_SUITE(test_init_ambiant);
	RUN_SUITE(test_init_camera);
	RUN_SUITE(test_init_sphere);
	RUN_SUITE(test_init_light);
	RUN_SUITE(test_init_plane);
	RUN_SUITE(test_init_cylinder);
	RUN_SUITE(test_parsing);
	GREATEST_MAIN_END();
}
