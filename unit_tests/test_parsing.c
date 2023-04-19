/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:34:03 by gpasquet          #+#    #+#             */
/*   Updated: 2023/04/19 15:22:16 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include "../includes/minirt.h"

TEST	ASSERT_CAM_EQ(t_camera *actual, t_camera *expected)
{
	ASSERT_EQ_FMT(expected->fov, actual->fov, "%f");
	ASSERT_EQ_FMT(expected->vector->x_o, actual->vector->x_o, "%f");
	ASSERT_EQ_FMT(expected->vector->y_o, actual->vector->y_o, "%f");
	ASSERT_EQ_FMT(expected->vector->z_o, actual->vector->z_o, "%f");
	ASSERT_EQ_FMT(expected->vector->x_d, actual->vector->x_d, "%f");
	ASSERT_EQ_FMT(expected->vector->y_d, actual->vector->y_d, "%f");
	ASSERT_EQ_FMT(expected->vector->z_d, actual->vector->z_d, "%f");
	PASS();
}

TEST	ASSERT_SPHERE_EQ(t_sphere *actual, t_sphere *expected)
{
	ASSERT_EQ_FMT(expected->pos->x, actual->pos->x, "%f");
	ASSERT_EQ_FMT(expected->pos->y, actual->pos->y, "%f");
	ASSERT_EQ_FMT(expected->pos->z, actual->pos->z, "%f");
	ASSERT_EQ_FMT(expected->diameter, actual->diameter, "%f");
	ASSERT_EQ_FMT(expected->color, actual->color, "%i");
	PASS();
}

TEST	ASSERT_AMB_L_EQ(t_ambiant_l	*actual, t_ambiant_l *expected)
{
	ASSERT_EQ_FMT(expected->light_ratio, actual->light_ratio, "%f");
	ASSERT_EQ_FMT(expected->colors, actual->colors, "%i");
	PASS();
}

TEST	ASSERT_SCENE_EQ(t_scene *actual, t_scene *expected)
{
	CHECK_CALL(ASSERT_AMB_L_EQ(actual->ambiant_l, expected->ambiant_l));
	CHECK_CALL(ASSERT_CAM_EQ(actual->camera, expected->camera));
	while (actual->obj_list)
	{
	//	if (obj_list->type == sphere)
			CHECK_CALL(ASSERT_SPHERE_EQ(actual->obj_list->obj, expected->obj_list->obj));
			actual->obj_list = actual->obj_list->next;
	}
	PASS();
}

TEST	correct_input(void) {
	t_scene	*scene1 = parsing("scenes/basic.rt");
	t_scene	*scene2 = parsing("scenes/unnecessary_lines.rt");
	t_scene	*expected = malloc(sizeof(t_scene));
	expected->ambiant_l = init_ambiant_l("A 0.2 255,255,255");
	expected->camera = init_camera("C -50,0,20 0,0,0 70");
	expected->obj_list = malloc(sizeof(t_obj_list));
	expected->obj_list->type = sphere;
	expected->obj_list->obj = init_sphere("sp 0,0,20 20 255,0,0");
	expected->obj_list->next = NULL;

	CHECK_CALL(ASSERT_SCENE_EQ(scene1, expected));
	CHECK_CALL(ASSERT_SCENE_EQ(scene2, expected));
	PASS();
}

TEST	wrong_path(void) {
	t_scene	*scene1 = parsing("test");
	t_scene	*scene2 = parsing(NULL);
	t_scene	*scene3 = parsing("test.yooooo");
	t_scene	*scene4 = parsing("test.rttt");

	ASSERT_EQ_FMT(NULL, scene1, "%p");
	ASSERT_EQ_FMT(NULL, scene2, "%p");
	ASSERT_EQ_FMT(NULL, scene3, "%p");
	ASSERT_EQ_FMT(NULL, scene4, "%p");
	PASS();
}

TEST	no_cam(void) {
	t_scene	*scene1 = parsing("scenes/wrong_scenes/no_camera.rt");

	ASSERT_EQ_FMT(NULL, scene1, "%p");
	PASS();
}

TEST	no_ambiant(void) {
	t_scene	*scene1 = parsing("scenes/wrong_scenes/no_ambiant.rt");

	ASSERT_EQ_FMT(NULL, scene1, "%p");
	PASS();
}
/*
TEST	no_light(void) {
	t_scene	*scene1 = parsing("no_light.rt");

	ASSERT_EQ_FMT(NULL, scene1, "%p");
	PASS();
}
*/
SUITE(test_parsing) {
	RUN_TEST(correct_input);
	RUN_TEST(wrong_path);
	RUN_TEST(no_cam);
	RUN_TEST(no_ambiant);
//	RUN_TEST(no_light);
}
