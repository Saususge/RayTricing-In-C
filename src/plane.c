/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:12:52 by chakim            #+#    #+#             */
/*   Updated: 2025/06/26 23:48:24 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "unistd.h"
#include "vector.h"
#include <stdlib.h>

static t_object_ops	g_plane_ops = {
	.intersect = &plane_intersect,
	.get_normal = NULL,
	.rotate = NULL,
	.translate = NULL,
	.get_color = NULL,
	.free = NULL
};

t_object	*create_plane(t_point point, t_vec3 normal, t_color color)
{
	t_object	*obj;
	t_plane		*pl;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	pl = malloc(sizeof(t_plane));
	if (!pl)
	{
		free(obj);
		return (NULL);
	}
	pl->point = point;
	pl->normal = normal;
	pl->color = color;
	obj->type = PLANE;
	obj->data = pl;
	obj->ops = &g_plane_ops;
	return (obj);
}

int	plane_intersect(t_object *this, t_ray *ray, t_hit *hit)
{
	t_plane	*pl;	
	float	denominator;
	float	t;
	t_vec3	p0_to_l0;

	pl = (t_plane *)this->data;
	denominator = vec3_dot(ray->direction, pl->normal);
	if (fabs(denominator) < EPSILON)
		return (0);
	p0_to_l0 = vec3_sub(point_to_vec3(pl->point), ray->origin);
	t = vec3_dot(p0_to_l0, pl->normal) / denominator;
	if (t < EPSILON)
		return (0);
	hit->t = t;
	hit->point = vec3_to_point(vec3_add(ray->origin, \
		vec3_mul(ray->direction, t)));
	hit->is_front_face = vec3_dot(ray->direction, pl->normal) < 0;
	if (hit->is_front_face)
		hit->normal = pl->normal;
	else
		hit->normal = vec3_neg(pl->normal);
	hit->color = pl->color;
	hit->object = this;
	return (1);
}
