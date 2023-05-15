/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:53:08 by gpasquet          #+#    #+#             */
/*   Updated: 2023/05/15 10:01:11 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"

TEST	ASSERT_CAM_EQ(t_camera *actual, t_camera *expected)
{
	ASSERT_EQ_FMT(expected->fov, actual->fov, "%f");
	ASSERT_EQ_FMT(expected->origin->x, actual->origin->x, "%f");
	ASSERT_EQ_FMT(expected->origin->y, actual->origin->y, "%f");
	ASSERT_EQ_FMT(expected->origin->z, actual->origin->z, "%f");
	ASSERT_EQ_FMT(expected->direction->x, actual->direction->x, "%f");
	ASSERT_EQ_FMT(expected->direction->y, actual->direction->y, "%f");
	ASSERT_EQ_FMT(expected->direction->z, actual->direction->z, "%f");
	PASS();
}

TEST	correct_input(void) {
	t_camera	*cam1 = init_camera("C -50.0,0,20 0,0,1 70");
	t_camera	*expected = malloc(sizeof(t_camera));
	expected->fov = 70 * (M_PI / 180);
	expected->origin = init_vector("-50.0,0,20");
	expected->direction = init_vector("0,0,1");
	ASSERT_CAM_EQ(cam1, expected);
	free_camera(&cam1);
	free_camera(&expected);
	PASS();
}

TEST	wrong_fov(void) {
	t_camera	*cam1 = init_camera("C -50.0,0,20 0,0,1 700");
	t_camera	*cam2 = init_camera("C -50.0,0,20 0,0,1 -70");

	ASSERT_EQ_FMT(NULL, cam1, "%p");
	ASSERT_EQ_FMT(NULL, cam2, "%p");
	PASS();
}

TEST	wrong_pos(void) {
	t_camera	*cam1 = init_camera("C -50a.0,0,20 0,0,1 70");
	t_camera	*cam2 = init_camera("C -50a.0,q0,20 0,0,1 70");
	t_camera	*cam3 = init_camera("C -50a.0,0,2w0 0,0,1 70");

	ASSERT_EQ_FMT(NULL, cam1, "%p");
	ASSERT_EQ_FMT(NULL, cam2, "%p");
	ASSERT_EQ_FMT(NULL, cam3, "%p");
	PASS();
}

TEST	wrong_orientation(void) {
	t_camera	*cam1 = init_camera("C -50.0,0,20 10,1.10,-1.01 70");
	t_camera	*cam2 = init_camera("C -50.0,0,20 1,1.10,1 70");
	t_camera	*cam3 = init_camera("C -50.0,0,20 1,0,-1.01 70");

	ASSERT_EQ_FMT(NULL, cam1, "%p");
	ASSERT_EQ_FMT(NULL, cam2, "%p");
	ASSERT_EQ_FMT(NULL, cam3, "%p");
	PASS();
}

SUITE(test_init_camera) {
	RUN_TEST(correct_input);
	RUN_TEST(wrong_pos);
	RUN_TEST(wrong_fov);
	RUN_TEST(wrong_orientation);
}
