/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/08 15:26:04 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "vector.h"
#include "rotate.h"
#include <math.h>

extern t_object_ops	g_plane_ops;

void	init_plane_basic(t_object *pl, t_vec3 color)
{
	pl->type = PLANE;
	pl->ops = &g_plane_ops;
	pl->color = color;
	pl->checkerboard = 0;
}

void	init_transform_matrix(t_object *pl, t_point point)
{
	pl->t = (t_mat){{{1, 0, 0, point.x},
	{0, 1, 0, point.y},
	{0, 0, 1, point.z},
	{0, 0, 0, 1}}};
}

void	init_rotation_matrix(t_object *pl, t_vec3 normal)
{
	t_vec3	axis;
	float	theta;

	axis = vec3_cross((t_vec3){0, 0, 1}, normal);
	if (vec3_length(axis) < EPSILON)
	{
		if (normal.z > 0.0f)
			pl->r = (t_mat){{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}}};
		else
			pl->r = (t_mat){{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, -1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, -1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}}};
	}
	else
	{
		axis = vec3_normalize(axis);
		theta = acosf(normal.z);
		rodrigues_to_mat4(axis, theta, &pl->r);
	}
}

t_vec4	plane_get_normal(const t_object *obj, t_vec4 p_local)
{
	(void)obj;
	(void)p_local;
	return ((t_vec4){{0.0f, 0.0f, 1.0f, 0.0f}});
}
