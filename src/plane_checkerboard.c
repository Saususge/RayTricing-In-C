/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_checkerboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:33:11 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 18:00:23 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include <math.h>

static t_vec3	get_plane_u_axis(t_vec3 normal)
{
	if (fabsf(normal.x) < 0.9f)
		return ((t_vec3){1, 0, 0});
	return ((t_vec3){0, 1, 0});
}

static void	get_plane_uv_coords(t_vec3 rel, t_vec3 normal, float *u, float *v)
{
	t_vec3	u_axis;
	t_vec3	u_dir;
	t_vec3	v_dir;

	u_axis = get_plane_u_axis(normal);
	u_dir = vec3_normalize(vec3_cross(normal, u_axis));
	v_dir = vec3_normalize(vec3_cross(normal, u_dir));
	*u = vec3_dot(rel, u_dir);
	*v = vec3_dot(rel, v_dir);
}

static t_vec3	plane_checkerboard_color_at(float u, float v)
{
	int	checker;

	checker = (int)(floorf(u * 0.23) + floorf(v * 0.23));
	if (checker % 2 == 0)
		return ((t_vec3){0, 0, 0});
	return ((t_vec3){255, 255, 255});
}

t_vec3	plane_get_color(const t_object *obj, t_point hit_point)
{
	t_vec3	rel;
	float	u;
	float	v;

	if (obj->checkerboard == 0)
		return (obj->color);
	rel = vec3_sub(hit_point, obj->data.plane.point);
	get_plane_uv_coords(rel, obj->data.plane.normal, &u, &v);
	return (plane_checkerboard_color_at(u, v));
}
