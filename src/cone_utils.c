/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 18:05:23 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include <math.h>

t_vec3	get_cone_u_axis(t_vec3 axis)
{
	t_vec3	u_axis;

	u_axis = (t_vec3){1.0f, 0.0f, 0.0f};
	if (fabsf(vec3_dot(axis, u_axis)) > 0.999f)
		u_axis = (t_vec3){0.0f, 1.0f, 0.0f};
	return (u_axis);
}

void	calculate_cone_uv_dirs(t_vec3 axis, t_vec3 *u_dir, t_vec3 *v_dir)
{
	t_vec3	u_axis;

	u_axis = get_cone_u_axis(axis);
	*u_dir = vec3_normalize(vec3_cross(axis, u_axis));
	*v_dir = vec3_normalize(vec3_cross(axis, *u_dir));
}

void	cone_lateral_uv(t_point p, const t_cone *cone, float *u, float *v)
{
	t_vec3	center_to_hit;
	t_vec3	u_dir;
	t_vec3	v_dir;
	float	height_ratio;

	center_to_hit = vec3_sub(p, cone->center);
	height_ratio = vec3_dot(center_to_hit, cone->axis) / cone->height;
	*v = height_ratio;
	calculate_cone_uv_dirs(cone->axis, &u_dir, &v_dir);
	*u = (atan2f(vec3_dot(center_to_hit, v_dir), \
		vec3_dot(center_to_hit, u_dir)) + M_PI) / (2.0f * M_PI);
}

void	cone_cap_uv(t_cone_cap_data data, float *u, float *v)
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
	rel = vec3_sub(data.p, data.cap_center);
	*u = 0.5f + vec3_dot(rel, u_dir) / (2.0f * data.radius);
	*v = 0.5f + vec3_dot(rel, v_dir) / (2.0f * data.radius);
}
