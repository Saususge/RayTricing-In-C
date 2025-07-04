/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_checkerboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 18:10:42 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include <math.h>

static t_vec3	get_cone_cap_color(t_point hit_point, const t_cone *cone)
{
	t_cone_cap_data	data;
	t_point			cap_center;
	float			u;
	float			v;

	cap_center = vec3_add(cone->center, vec3_mul(cone->axis, cone->height));
	data.p = hit_point;
	data.cap_center = cap_center;
	data.axis = cone->axis;
	data.radius = cone->radius;
	cone_cap_uv(data, &u, &v);
	return (checkerboard_color_at(u, v));
}

static int	is_cone_cap_hit(t_point hit_point, const t_cone *cone)
{
	t_vec3	center_to_hit;
	float	projection;

	center_to_hit = vec3_sub(hit_point, cone->center);
	projection = vec3_dot(center_to_hit, cone->axis);
	return (fabsf(projection - cone->height) < EPSILON);
}

t_vec3	cone_get_color(const t_object *obj, t_point hit_point)
{
	float	u;
	float	v;

	if (obj->checkerboard == 0)
		return (obj->color);
	if (is_cone_cap_hit(hit_point, &obj->data.cone))
		return (get_cone_cap_color(hit_point, &obj->data.cone));
	cone_lateral_uv(hit_point, &obj->data.cone, &u, &v);
	return (checkerboard_color_at(u, v));
}
