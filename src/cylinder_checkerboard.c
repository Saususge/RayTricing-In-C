/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_checkerboard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:05:15 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 18:03:17 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include <math.h>

static void	cylinder_cap_uv(t_cap_uv_data data, float *u, float *v)
{
	t_vec3	u_axis;
	t_vec3	u_dir;
	t_vec3	v_dir;
	t_vec3	rel;

	if (fabsf(data.axis.x) < 0.9f)
		u_axis = (t_vec3){1, 0, 0};
	else
		u_axis = (t_vec3){0, 1, 0};
	u_dir = vec3_normalize(vec3_cross(data.axis, u_axis));
	v_dir = vec3_normalize(vec3_cross(data.axis, u_dir));
	rel = vec3_sub(data.p, data.center);
	*u = 0.5f + vec3_dot(rel, u_dir) / (4.0f * data.radius);
	*v = 0.5f + vec3_dot(rel, v_dir) / (4.0f * data.radius);
}

static t_vec3	get_cap_color(t_point hit_point, t_point cap_center, \
	t_vec3 axis, float radius)
{
	t_cap_uv_data	data;
	float			u;
	float			v;

	data.p = hit_point;
	data.center = cap_center;
	data.axis = axis;
	data.radius = radius;
	cylinder_cap_uv(data, &u, &v);
	return (checkerboard_color_at(u, v));
}

t_vec3	cylinder_get_color(const t_object *obj, t_point hit_point)
{
	t_vec3	p_to_hit;
	float	proj;
	float	u;
	float	v;

	if (obj->checkerboard == 0)
		return (obj->color);
	p_to_hit = vec3_sub(hit_point, obj->data.cylinder.p1);
	proj = vec3_dot(p_to_hit, obj->data.cylinder.axis);
	if (proj < EPSILON)
		return (get_cap_color(hit_point, obj->data.cylinder.p1, \
			obj->data.cylinder.axis, obj->data.cylinder.radius));
	if (proj > obj->data.cylinder.height - EPSILON)
		return (get_cap_color(hit_point, obj->data.cylinder.p2, \
			obj->data.cylinder.axis, obj->data.cylinder.radius));
	cylinder_get_uv(hit_point, &obj->data.cylinder, &u, &v);
	return (checkerboard_color_at(u, v));
}
