/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_checkerboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:07:12 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 18:00:16 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include <math.h>

static t_vec3	get_sphere_relative_point(t_point hit_point, t_vec3 center)
{
	return (vec3_sub(hit_point, center));
}

static void	get_sphere_uv_coords(t_vec3 p, float radius, float *u, float *v)
{
	*u = 0.5f + atan2f(p.z, p.x) / (2.0f * M_PI);
	*v = 0.5f - asinf(p.y / radius) / M_PI;
}

t_vec3	sphere_get_color(const t_object *obj, t_point hit_point)
{
	t_vec3	p;
	float	u;
	float	v;

	if (obj->checkerboard == 0)
		return (obj->color);
	p = get_sphere_relative_point(hit_point, obj->data.sphere.center);
	get_sphere_uv_coords(p, obj->data.sphere.radius, &u, &v);
	return (checkerboard_color_at(u, v));
}
