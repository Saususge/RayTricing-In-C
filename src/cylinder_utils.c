/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:15:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 18:03:04 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include <math.h>

t_vec3	get_cylinder_u_axis(t_vec3 axis)
{
	t_vec3	u_axis;

	u_axis = (t_vec3){1.0f, 0.0f, 0.0f};
	if (fabsf(vec3_dot(axis, u_axis)) > 0.999f)
		u_axis = (t_vec3){0.0f, 1.0f, 0.0f};
	return (u_axis);
}

void	calculate_cylinder_uv_dirs(t_vec3 axis, t_vec3 *u_dir, t_vec3 *v_dir)
{
	t_vec3	u_axis;

	u_axis = get_cylinder_u_axis(axis);
	*u_dir = vec3_normalize(vec3_cross(axis, u_axis));
	*v_dir = vec3_normalize(vec3_cross(axis, *u_dir));
}

void	cylinder_get_uv(t_point p, const t_cylinder *cy, float *u, float *v)
{
	t_vec3	hit_vec;
	t_vec3	u_dir;
	t_vec3	v_dir;

	hit_vec = vec3_sub(p, cy->p1);
	*v = vec3_dot(hit_vec, cy->axis) / cy->height;
	calculate_cylinder_uv_dirs(cy->axis, &u_dir, &v_dir);
	hit_vec = vec3_sub(p, cy->center);
	*u = (atan2f(vec3_dot(hit_vec, v_dir), \
	vec3_dot(hit_vec, u_dir)) + M_PI) / (2.0f * M_PI);
}
