/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_2.c                                        :+:      :+:    :+:   */
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

void	add_diffuse(const t_light *light, \
	const t_hit *hit, t_vec3 *diff, const t_object *this)
{
	float	diff_dot;
	float	distance_sq;
	float	attenuation;
	t_vec3	light_intensity;

	diff_dot = fmaxf(vec3_dot(hit->normal, \
		get_light_dir(light, hit)), 0.0f);
	distance_sq = point_distance_squared(hit->point, light->position);
	attenuation = 1.0f / (distance_sq + 1.0f);
	light_intensity = vec3_mul(light->intensity, \
		g()->k_d * diff_dot * attenuation);
	*diff = vec3_add(*diff, vec3_hadamard(light_intensity, this->color));
}

float	calc_spec_factor(const t_light *light, \
	const t_hit *hit, t_vec3 reflect_dir)
{
	float	shininess;
	t_vec3	view_dir;
	float	spec_dot;
	float	attenuation;

	shininess = 64.0f;
	view_dir = vec3_normalize(vec3_sub(g()->cam.pos, hit->point));
	spec_dot = fmaxf(vec3_dot(view_dir, reflect_dir), 0.0f);
	attenuation = 1.0f / (point_distance_squared(hit->point, \
		light->position) + 1.0f);
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
	reflect_dir = vec3_normalize(vec3_reflect(vec3_neg(light_dir), \
	hit->normal));
	spec_factor = calc_spec_factor(light, hit, reflect_dir);
	spec_light_intensity = vec3_mul(light->intensity, spec_factor);
	*spec = vec3_add(*spec, vec3_hadamard(spec_color, spec_light_intensity));
}

void	calc_diff_spec(const t_hit *hit, t_vec3 *diff, \
	t_vec3 *spec, const t_object *this)
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
