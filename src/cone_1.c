/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:44:51 by chakim            #+#    #+#             */
/*   Updated: 2025/07/07 17:34:06 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include "vector.h"
#include "rotate.h"
#include <math.h>
#include <unistd.h>

int	cone_intersect(const t_object *obj, const t_ray *ray_world, \
	t_intersect *record, t_interval t_bound)
{
	t_ray	local_ray;
	float	t;
	int		lateral_hit;
	int		cap_hit;

	local_ray.o = mat_mul_vec4(&obj->m_inv, ray_world->o);
	local_ray.d = mat_mul_vec4(&obj->m_inv, ray_world->d);
	lateral_hit = cone_lateral_intersect(obj, &local_ray, &t, t_bound);
	if (lateral_hit)
		cap_hit = cone_intersect_cap(obj, &local_ray, &t, \
			(t_interval){t_bound.min, t});
	else
		cap_hit = cone_intersect_cap(obj, &local_ray, &t, t_bound);
	if (!lateral_hit && !cap_hit)
		return (0);
	record->t = t;
	record->p_local = vec4_add(local_ray.o, vec4_mul(local_ray.d, t));
	record->n_local = cone_get_normal(record->p_local);
	record->obj = (t_object *)obj;
	return (1);
}

t_vec4	cone_get_normal(t_vec4 p_local)
{
	t_vec4	n;

	if (fabs(p_local.v[2] - 1.0f) < EPSILON)
		return ((t_vec4){{0, 0, 1, 0}});
	n = (t_vec4){{p_local.v[0], p_local.v[1], -p_local.v[2], 0}};
	n = vec4_mul(n, 1.0f / (sqrtf(2)) * p_local.v[2]);
	return (n);
}
