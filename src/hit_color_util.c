/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_color_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:25 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/05 13:44:31 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "object.h"

t_vec3	clamp_color_vec3(t_vec3 color)
{
	color = vec3_max(color, (t_vec3){0, 0, 0});
	color = vec3_min(color, (t_vec3){255, 255, 255});
	return (color);
}

static void	set_hit_geometry(t_hit *hit, float t, const t_ray *ray,
	const t_object *this)
{
	hit->t = t;
	hit->normal
		= this->ops->get_normal(this, vec4_add(ray->o, vec4_mul(ray->d, t)));
	hit->is_front_face = vec4_dot(ray->d, hit->normal) < 0;
	if (!hit->is_front_face)
		hit->normal = vec4_neg(hit->normal);
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
	amb = ambient_term(this, hit->point);
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

	shadow_ray.o = hit->point;
	shadow_ray.d = get_light_dir(light, hit);
	dist = point_distance(light->position, hit->point);
	return (!hit_shadow(&shadow_ray, EPSILON, dist - EPSILON));
}
