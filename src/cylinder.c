/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/07/07 21:21:57 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include "rotate.h"
#include <unistd.h>

static t_object_ops	g_cylinder_ops = {
	.intersect = cylinder_intersect,
	.get_color = cylinder_get_color,
};

// Assume that the cylinder is centered at the origin in local space, and
// the axis is aligned with the z-axis. The height is 1 and the radius is 1.
// The `data` struct contains 
t_object	create_cylinder(struct s_cyl_data data)
{
	t_object	cyl;
	t_mat		temp;
	t_vec3		axis;
	float		theta;

	cyl.type = CYLINDER;
	cyl.ops = &g_cylinder_ops;
	cyl.color = data.color;
	cyl.checkerboard = 0;
	cyl.t = (t_mat){{{1, 0, 0, data.center.x},
	{0, 1, 0, data.center.y},
	{0, 0, 1, data.center.z},
	{0, 0, 0, 1}}};
	axis = vec3_cross((t_vec3){0, 0, 1}, data.axis);
	if (vec3_length(axis) < EPSILON)
	{
		if (data.axis.z > 0.0f)
			cyl.r = (t_mat){{
				{1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 1.0f, 0.0f},
				{0.0f, 0.0f, 0.0f, 1.0f}}};
		else
			cyl.r = (t_mat){{
				{1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, -1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, -1.0f, 0.0f},
				{0.0f, 0.0f, 0.0f, 1.0f}}};
	}
	else
	{
		axis = vec3_normalize(axis);
		theta = acosf(data.axis.z);
		rodrigues_to_mat4(axis, theta, &cyl.r);
	}
	cyl.s = (t_mat){{{data.radius, 0, 0, 0},
	{0, data.radius, 0, 0},
	{0, 0, data.height, 0},
	{0, 0, 0, 1}}};
	mat_mul_mat(&cyl.r, &cyl.s, &temp);
	mat_mul_mat(&cyl.t, &temp, &cyl.m);
	mat_inverse(&cyl.m, &cyl.m_inv);
	return (cyl);
}
