/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:25:34 by chakim            #+#    #+#             */
/*   Updated: 2025/07/05 12:08:12 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include "vector.h"
#include "rotate.h"
#include <math.h>
#include <unistd.h>

int	cone_intersect_cap(
	const t_cone *cone,
	const t_ray *ray,
	float *t,
	t_t_bound bound)
{
	float	temp_t;
	float	denom;
	t_vec3	oc;
	t_point	hit_point;
	t_vec3	cap_to_hit;

	denom = vec3_dot(ray->d, cone->axis);
	if (fabs(denom) < EPSILON)
		return (0);
	oc = vec3_sub(
			vec3_add(cone->center, vec3_mul(cone->axis, cone->height)),
			ray->o);
	temp_t = vec3_dot(oc, cone->axis) / denom;
	if (temp_t < bound.min || temp_t > bound.max)
		return (0);
	hit_point = vec3_add(ray->o, vec3_mul(ray->d, temp_t));
	cap_to_hit = vec3_sub(
			hit_point,
			vec3_add(cone->center, vec3_mul(cone->axis, cone->height)));
	if (vec3_dot(cap_to_hit, cap_to_hit) > cone->radius * cone->radius)
		return (0);
	*t = temp_t;
	return (1);
}

void	cone_scale(t_object *this, float scale)
{
	this->data.cone.radius *= scale;
	this->data.cone.height *= scale;
}
