/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 22:00:06 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include "rotate.h"
#include <unistd.h>

int	cylinder_intersect(const t_object *this,
						const t_ray *ray,
						t_hit *hit,
						t_t_bound bound)
{
	int			lateral_hit;
	int			cap_hit;
	float		t;

	lateral_hit = intersect_lateral(&this->data.cylinder, ray, &t, bound);
	if (lateral_hit)
		cap_hit = intersect_cap(&this->data.cylinder, ray, &t, \
			(t_t_bound){bound.min, t});
	else
		cap_hit = intersect_cap(&this->data.cylinder, ray, &t, bound);
	if (!lateral_hit && !cap_hit)
		return (0);
	populate_hit_record(hit, t, ray, this);
	return (1);
}

int	cylinder_shadow_intersect(const t_object *this,
						const t_ray *ray,
						t_t_bound bound)
{
	int			lateral_hit;
	int			cap_hit;
	float		t;

	lateral_hit = intersect_lateral(&this->data.cylinder, ray, &t, bound);
	if (lateral_hit)
		cap_hit = intersect_cap(&this->data.cylinder, ray, &t, \
			(t_t_bound){bound.min, t});
	else
		cap_hit = intersect_cap(&this->data.cylinder, ray, &t, bound);
	if (!lateral_hit && !cap_hit)
		return (0);
	return (1);
}

t_vec3	cylinder_get_normal(const t_object *this, const t_point *hit_point)
{
	t_cylinder	cyl;
	t_vec3		p1_to_hit;
	float		projection;
	t_vec3		projection_point;
	t_vec3		normal;

	cyl = this->data.cylinder;
	p1_to_hit = vec3_sub(*hit_point, this->data.cylinder.p1);
	projection = vec3_dot(p1_to_hit, cyl.axis);
	if (fabs(projection) < EPSILON)
		return (vec3_neg(cyl.axis));
	if (fabs(projection - cyl.height) < EPSILON)
		return (cyl.axis);
	projection_point = vec3_add(this->data.cylinder.p1, \
		vec3_mul(cyl.axis, projection));
	normal = vec3_mul(vec3_sub(*hit_point, projection_point), \
	1.0f / cyl.radius);
	return (normal);
}
