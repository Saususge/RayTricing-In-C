/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:44:51 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 21:32:18 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include "vector.h"
#include "rotate.h"
#include <math.h>
#include <unistd.h>

static void	fill_normal(t_intersect *record, const t_ray *local_ray,
	const t_ray *ray_world, float t)
{
	t_vec4	normal;

	record->p_local = vec4_add(local_ray->o, vec4_mul(local_ray->d, t));
	if (record->obj->bump)
		normal = get_bumped_normal_cone(record->p_local);
	else
		normal = cone_get_normal(record->p_local);
	record->n_world = mat_mul_vec4(&record->obj->n, normal);
	record->n_world.v[3] = 0.0f;
	record->n_world = vec4_mul(record->n_world, 1.0f / \
		sqrtf(vec4_dot(record->n_world, record->n_world)));
	if (vec4_dot(record->n_world, ray_world->d) > 0.0f)
		record->n_world = vec4_neg(record->n_world);
}

int	cone_intersect(const t_object *obj, const t_ray *ray_world, \
	t_intersect *record, t_interval t_bound)
{
	t_ray	local_ray;
	float	t;
	int		lateral_hit;
	int		cap_hit;

	local_ray.o = mat_mul_vec4(&obj->m_inv, ray_world->o);
	local_ray.d = mat_mul_vec4(&obj->m_inv, ray_world->d);
	lateral_hit = cone_lateral_intersect(&local_ray, &t, t_bound);
	if (lateral_hit)
		cap_hit = cone_intersect_cap(&local_ray, &t, \
			(t_interval){t_bound.min, t});
	else
		cap_hit = cone_intersect_cap(&local_ray, &t, t_bound);
	if (!lateral_hit && !cap_hit)
		return (0);
	record->t = t;
	record->obj = (t_object *)obj;
	fill_normal(record, &local_ray, ray_world, t);
	return (1);
}
