/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_color_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:25 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 18:31:58 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "object.h"

t_vec3	clamp_color_vec3(t_vec3 color)
{
	t_vec3	minv;
	t_vec3	maxv;

	minv.x = 0;
	minv.y = 0;
	minv.z = 0;
	maxv.x = 255;
	maxv.y = 255;
	maxv.z = 255;
	color = vec3_max(color, minv);
	color = vec3_min(color, maxv);
	return (color);
}

static void	set_hit_geometry(t_hit *hit, float t, const t_ray *ray,
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

void	populate_hit_record(t_hit *hit, float t,
	const t_ray *ray, const t_object *this)
{
	t_vec3	amb;
	t_vec3	diff;
	t_vec3	spec;
	t_vec3	result;

	set_hit_geometry(hit, t, ray, this);
	amb = calc_ambient(this, hit->point);
	diff.x = 0;
	diff.y = 0;
	diff.z = 0;
	spec.x = 0;
	spec.y = 0;
	spec.z = 0;
	calc_diff_spec(hit, &diff, &spec, this);
	result = vec3_add(vec3_add(amb, diff), spec);
	hit->color = clamp_color_vec3(result);
}

int	is_lit(const t_light *light, const t_hit *hit)
{
	t_ray	shadow_ray;
	float	dist;

	shadow_ray.origin = hit->point;
	shadow_ray.dir = get_light_dir(light, hit);
	dist = point_distance(light->position, hit->point);
	return (!hit_shadow(&shadow_ray, EPSILON, dist - EPSILON));
}
