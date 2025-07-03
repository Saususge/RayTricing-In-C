/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/07/03 17:59:24 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include "rotate.h"
#include <unistd.h>

void	cylinder_translate(t_object *this, t_vec3 offset)
{
	this->data.cylinder.p1 = vec3_add(this->data.cylinder.p1, offset);
	this->data.cylinder.p2 = vec3_add(this->data.cylinder.p2, offset);
	this->data.cylinder.center = vec3_add(this->data.cylinder.center, offset);
}

void	cylinder_rotate(t_object *this, t_vec3 angle)
{
	this->data.cylinder.axis = rotate_vector(this->data.cylinder.axis, angle);
	this->data.cylinder.p1 = vec3_add(
			this->data.cylinder.center,
			vec3_mul(this->data.cylinder.axis,
				-this->data.cylinder.height * 0.5f));
	this->data.cylinder.p2 = vec3_add(
			this->data.cylinder.center,
			vec3_mul(this->data.cylinder.axis,
				this->data.cylinder.height * 0.5f));
}

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

void	cylinder_scale(t_object *this, float scale)
{
	this->data.cylinder.radius *= scale;
	this->data.cylinder.height *= scale;
	this->data.cylinder.p1 = vec3_add(
			this->data.cylinder.center,
			vec3_mul(this->data.cylinder.axis,
				-this->data.cylinder.height * 0.5f));
	this->data.cylinder.p2 = vec3_add(
			this->data.cylinder.center,
			vec3_mul(this->data.cylinder.axis,
				this->data.cylinder.height * 0.5f));
}
