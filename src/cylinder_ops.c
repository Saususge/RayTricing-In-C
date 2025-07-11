/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/07/11 13:36:26 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include "rotate.h"
#include <unistd.h>

static t_vec4	cylinder_get_normal(t_vec4 p_local)
{
	if (fabsf(p_local.v[2] - 0.5f) < EPSILON)
		return ((t_vec4){{0.0f, 0.0f, 1.0f, 0.0f}});
	else if (fabsf(p_local.v[2] + 0.5f) < EPSILON)
		return ((t_vec4){{0.0f, 0.0f, -1.0f, 0.0f}});
	else
		return ((t_vec4){{p_local.v[0], p_local.v[1], 0.0f, 0.0f}});
}

static void	fill_normal(t_intersect *record, const t_ray *local_ray,
	const t_ray *ray_world, float t)
{
	t_vec4	normal;

	record->p_local = vec4_add(local_ray->o, vec4_mul(local_ray->d, t));
	normal = cylinder_get_normal(record->p_local);
	record->n_world = mat_mul_vec4(&record->obj->n, normal);
	record->n_world.v[3] = 0.0f;
	record->n_world = vec4_mul(record->n_world, 1.0f / \
		sqrtf(vec4_dot(record->n_world, record->n_world)));
	if (vec4_dot(record->n_world, ray_world->d) > 0.0f)
		record->n_world = vec4_neg(record->n_world);
}

int	cylinder_intersect(const t_object *obj, \
	const t_ray *ray_world, t_intersect *record, t_interval t_bound)
{
	t_ray	local_ray;
	int		lateral_hit;
	int		cap_hit;
	float	t;

	local_ray.o = mat_mul_vec4(&obj->m_inv, ray_world->o);
	local_ray.d = mat_mul_vec4(&obj->m_inv, ray_world->d);
	lateral_hit = intersect_lateral(&local_ray, t_bound, &t);
	if (lateral_hit)
		cap_hit = intersect_cap(&local_ray, (t_interval){t_bound.min, t}, &t);
	else
		cap_hit = intersect_cap(&local_ray, t_bound, &t);
	if (!lateral_hit && !cap_hit)
		return (0);
	record->t = t;
	record->obj = (t_object *)obj;
	fill_normal(record, &local_ray, ray_world, t);
	return (1);
}
