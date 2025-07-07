/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:56:03 by chakim            #+#    #+#             */
/*   Updated: 2025/07/07 23:15:57 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include "vector.h"
#include "rotate.h"
#include <math.h>
#include <unistd.h>

static t_object_ops	g_cone_ops = {
	.intersect = cone_intersect,
	.get_color = cone_get_color,
};

t_object	create_cone(struct s_cone_data data)
{
	t_object	cn;
	t_mat		temp;
	t_vec3		rotation_axis;
	float		angle;

	cn.type = CONE;
	cn.ops = &g_cone_ops;
	cn.color = data.color;
	cn.checkerboard = 0;
	cn.t = (t_mat){{
	{1.0f, 0.0f, 0.0f, data.center.x},
	{0.0f, 1.0f, 0.0f, data.center.y},
	{0.0f, 0.0f, 1.0f, data.center.z},
	{0.0f, 0.0f, 0.0f, 1.0f}}};
	rotation_axis = vec3_cross((t_vec3){0, 0, 1}, data.axis);
	if (vec3_length(rotation_axis) < EPSILON)
	{
		if (data.axis.z > 0.0f)
			cn.r = (t_mat){{
				{1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 1.0f, 0.0f},
				{0.0f, 0.0f, 0.0f, 1.0f}}};
		else
			cn.r = (t_mat){{
				{1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, -1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, -1.0f, 0.0f},
				{0.0f, 0.0f, 0.0f, 1.0f}}};
	}
	else
	{
		rotation_axis = vec3_normalize(rotation_axis);
		angle = acosf(data.axis.z);
		rodrigues_to_mat4(rotation_axis, angle, &cn.r);
	}
	cn.s = (t_mat){{
	{data.radius, 0.0f, 0.0f, 0.0f},
	{0.0f, data.radius, 0.0f, 0.0f},
	{0.0f, 0.0f, data.height, 0.0f},
	{0.0f, 0.0f, 0.0f, 1.0f}}};
	mat_mul_mat(&cn.r, &cn.s, &temp);
	mat_mul_mat(&cn.t, &temp, &cn.m);
	mat_inverse(&cn.m, &cn.m_inv);
	mat_transpose(&cn.m_inv, &cn.n);
	return (cn);
}
