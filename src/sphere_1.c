/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:00 by chakim            #+#    #+#             */
/*   Updated: 2025/07/01 15:00:00 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include "object.h"
#include <math.h>

void	set_hit_geometry(t_hit *hit, float t, const t_ray *ray, \
	const t_object *this)
{
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_mul(ray->dir, t));
	hit->normal = this->ops->get_normal(this, &hit->point);
	hit->is_front_face = vec3_dot(ray->dir, hit->normal) < 0;
	if (!hit->is_front_face)
		hit->normal = vec3_neg(hit->normal);
	hit->object = (t_object *)this;
}

t_vec3	calc_ambient(const t_object *this)
{
	t_vec3	amb;
	t_vec3	amb_intensity;

	amb_intensity = vec3_mul(g()->amb_light.intensity, \
	g()->k_a);
	amb = vec3_hadamard(amb_intensity, this->color);
	return (amb);
}

t_vec3	get_light_dir(const t_light *light, const t_hit *hit)
{
	return (vec3_normalize(vec3_sub(light->position, hit->point)));
}

float	get_light_distance(const t_light *light, const t_hit *hit)
{
	return (vec3_length(vec3_sub(light->position, hit->point)));
}

int	is_lit(const t_light *light, const t_hit *hit)
{
	t_ray	shadow_ray;
	float	dist;

	shadow_ray.origin = hit->point;
	shadow_ray.dir = get_light_dir(light, hit);
	dist = get_light_distance(light, hit);
	return (!hit_shadow(&shadow_ray, EPSILON, dist - EPSILON));
}
