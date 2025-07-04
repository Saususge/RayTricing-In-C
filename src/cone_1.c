/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:44:51 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 22:00:41 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include "vector.h"
#include "rotate.h"
#include <math.h>
#include <unistd.h>

int	cone_intersect(
		const t_object *this, const t_ray *ray, t_hit *hit, t_t_bound bound)
{
	float	t;
	int		lateral_hit;
	int		cap_hit;

	lateral_hit = cone_lateral_intersect(&this->data.cone, ray, &t, bound);
	if (lateral_hit)
		cap_hit = cone_intersect_cap(
				&this->data.cone, ray, &t, (t_t_bound){bound.min, t});
	else
		cap_hit = cone_intersect_cap(&this->data.cone, ray, &t, bound);
	if (!lateral_hit && !cap_hit)
		return (0);
	populate_hit_record(hit, t, ray, this);
	return (1);
}

int	cone_shadow_intersect(
		const t_object *this, const t_ray *ray, t_t_bound bound)
{
	float			t;
	int				lateral_hit;
	int				cap_hit;

	lateral_hit = cone_lateral_intersect(&this->data.cone, ray, &t, bound);
	if (lateral_hit)
		cap_hit = cone_intersect_cap(
				&this->data.cone, ray, &t, (t_t_bound){bound.min, t});
	else
		cap_hit = cone_intersect_cap(&this->data.cone, ray, &t, bound);
	if (lateral_hit || cap_hit)
		return (1);
	return (0);
}

t_vec3	cone_get_normal(const t_object *this, const t_point *hit_point)
{
	t_cone	cone;
	t_vec3	center_to_hit;
	float	projection;
	t_vec3	axis_point;
	t_vec3	normal;

	cone = this->data.cone;
	center_to_hit = vec3_sub(*hit_point, cone.center);
	projection = vec3_dot(center_to_hit, cone.axis);
	if (fabs(projection - cone.height) < EPSILON)
		return (cone.axis);
	axis_point = vec3_add(cone.center, vec3_mul(cone.axis, projection));
	normal = vec3_sub(*hit_point, axis_point);
	normal = vec3_sub(
			normal,
			vec3_mul(
				cone.axis,
				cone.radius / cone.height * vec3_length(normal)));
	return (vec3_normalize(normal));
}
