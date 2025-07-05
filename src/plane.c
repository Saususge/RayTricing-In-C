/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:12:52 by chakim            #+#    #+#             */
/*   Updated: 2025/07/05 12:08:12 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "unistd.h"
#include "vector.h"
#include <stdlib.h>
#include "rotate.h"

static t_object_ops	g_plane_ops = {
	.intersect = plane_intersect,
	.shadow_intersect = plane_shadow_intersect,
	.get_normal = plane_get_normal,
	.get_color = plane_get_color,
};

t_object	create_plane(t_point point, t_vec3 normal, t_vec3 color)
{
	return ((t_object){
		.type = PLANE,
		.ops = &g_plane_ops,
		.color = color,
		.checkerboard = 0,
	});
}

int	plane_intersect(const t_object *this, \
	const t_ray *ray, t_hit *hit, t_t_bound bound)
{
	t_plane	pl;	
	float	denominator;
	float	t;
	t_vec3	p0_to_l0;

	pl = this->data.plane;
	denominator = vec3_dot(ray->d, pl.normal);
	if (fabs(denominator) < EPSILON)
		return (0);
	p0_to_l0 = vec3_sub(pl.point, ray->o);
	t = vec3_dot(p0_to_l0, pl.normal) / denominator;
	if (t < bound.min || t > bound.max)
		return (0);
	populate_hit_record(hit, t, ray, this);
	return (1);
}

int	plane_shadow_intersect(const t_object *this, \
	const t_ray *ray, t_t_bound bound)
{
	t_plane	pl;	
	float	denominator;
	float	t;
	t_vec3	p0_to_l0;

	pl = this->data.plane;
	p0_to_l0 = vec3_sub(pl.point, ray->o);
	denominator = vec3_dot(ray->d, pl.normal);
	if (fabs(denominator) < EPSILON)
		return (0);
	t = vec3_dot(p0_to_l0, pl.normal) / denominator;
	if (t < bound.min || t > bound.max)
		return (0);
	return (1);
}
