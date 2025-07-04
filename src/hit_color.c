/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:25 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 17:20:25 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "hit.h"

t_vec3	calc_ambient(const t_object *this, t_point hit_point)
{
	t_vec3	amb;
	t_vec3	amb_intensity;

	amb_intensity = vec3_mul(g()->amb_light.intensity, g()->k_a);
	amb = vec3_hadamard(amb_intensity, this->ops->get_color(this, hit_point));
	return (amb);
}

void	add_diffuse(const t_light *light, const t_hit *hit, t_vec3 *diff,
	const t_object *this)
{
	float	diff_dot;
	float	distance_sq;
	float	attenuation;
	t_vec3	light_intensity;

	diff_dot = fmaxf(vec3_dot(hit->normal, get_light_dir(light, hit)), 0.0f);
	distance_sq = point_distance_squared(hit->point, light->position);
	attenuation = 1.0f / (distance_sq + 1.0f);
	light_intensity = vec3_mul(
			light->intensity, g()->k_d * diff_dot * attenuation);
	*diff = vec3_add(*diff,
			vec3_hadamard(
				light_intensity,
				this->ops->get_color(this, hit->point)));
}

float	calc_spec_factor(const t_light *light, const t_hit *hit,
	t_vec3 reflect_dir)
{
	float	shininess;
	t_vec3	view_dir;
	float	spec_dot;
	float	attenuation;

	shininess = 64.0f;
	view_dir = vec3_normalize(vec3_sub(g()->cam.pos, hit->point));
	spec_dot = fmaxf(vec3_dot(view_dir, reflect_dir), 0.0f);
	attenuation = 1.0f
		/ (point_distance_squared(hit->point, light->position) + 1.0f);
	return (powf(spec_dot, shininess) * g()->k_s * attenuation);
}

void	add_specular(const t_light *light, const t_hit *hit, t_vec3 *spec)
{
	t_vec3	spec_color;
	t_vec3	light_dir;
	t_vec3	reflect_dir;
	float	spec_factor;
	t_vec3	spec_light_intensity;

	spec_color.x = 255.0f;
	spec_color.y = 255.0f;
	spec_color.z = 255.0f;
	light_dir = get_light_dir(light, hit);
	reflect_dir = vec3_normalize(
			vec3_reflect(vec3_neg(light_dir), hit->normal));
	spec_factor = calc_spec_factor(light, hit, reflect_dir);
	spec_light_intensity = vec3_mul(light->intensity, spec_factor);
	*spec = vec3_add(*spec, vec3_hadamard(spec_color, spec_light_intensity));
}

void	calc_diff_spec(const t_hit *hit, t_vec3 *diff, t_vec3 *spec,
	const t_object *this)
{
	int		i;
	t_light	*light;

	i = 0;
	while (i < g()->light_count)
	{
		light = g()->lights + i;
		if (is_lit(light, hit))
		{
			add_diffuse(light, hit, diff, this);
			add_specular(light, hit, spec);
		}
		i++;
	}
}
