/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_def_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:00:00 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/08 00:00:00 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "object.h"

t_vec3	calculate_specular_light(const t_intersect *record, t_vec4 light_dir, \
	float attenuation, t_vec3 light_intensity)
{
	t_vec4	p_world;
	t_vec4	view_world;
	t_vec4	reflect_world;
	float	specular_dot;
	float	specular_factor;

	p_world = mat_mul_vec4(&record->obj->m, record->p_local);
	view_world = vec4_sub(vec3_to_vec4(g()->cam.pos, 1.0f), p_world);
	reflect_world = vec4_sub(vec4_neg(light_dir), \
		vec4_mul(record->n_world, 2.0f * \
			vec4_dot(vec4_neg(light_dir), record->n_world)));
	reflect_world.v[3] = 0.0f;
	specular_dot = fmaxf(vec4_dot(view_world, reflect_world) / \
		(sqrtf(vec4_dot(view_world, view_world) * \
		vec4_dot(reflect_world, reflect_world))), 0.0f);
	specular_factor = powf(specular_dot, SHININESS) * \
	K_SPECULAR * attenuation * g()->specular;
	return (vec3_mul(light_intensity, specular_factor * 255.0f));
}

int	is_in_shadow(const t_intersect *record, int light_idx)
{
	t_vec4	p_world;
	t_vec4	light_dir;
	float	distance;
	t_ray	shadow_ray;

	p_world = mat_mul_vec4(&record->obj->m, record->p_local);
	distance = calculate_light_distance \
	(g()->lights[light_idx].position, p_world);
	light_dir = calculate_light_direction \
	(g()->lights[light_idx].position, p_world);
	shadow_ray = (t_ray){.o = p_world, .d = light_dir};
	return (hit_shadow_ray(&shadow_ray, \
		(t_interval){EPSILON, distance - EPSILON}));
}

float	calculate_attenuation(const t_intersect *record, int light_idx)
{
	t_vec4	p_world;
	float	distance;

	p_world = mat_mul_vec4(&record->obj->m, record->p_local);
	distance = calculate_light_distance \
	(g()->lights[light_idx].position, p_world);
	return (1.0f / (1.0f + 0.05 * distance * distance));
}

t_vec3	process_single_light(const t_intersect *record, int light_idx)
{
	t_vec4	p_world;
	t_vec4	light_dir;
	float	attenuation;
	t_vec3	result;

	if (is_in_shadow(record, light_idx))
		return ((t_vec3){0, 0, 0});
	p_world = mat_mul_vec4(&record->obj->m, record->p_local);
	light_dir = calculate_light_direction \
	(g()->lights[light_idx].position, p_world);
	attenuation = calculate_attenuation(record, light_idx);
	result = calculate_diffuse_light \
	(record, light_dir, attenuation, g()->lights[light_idx].intensity);
	result = vec3_add(result, calculate_specular_light \
		(record, light_dir, attenuation, g()->lights[light_idx].intensity));
	return (result);
}

t_vec3	get_color(const t_intersect *record)
{
	t_vec3	ambient;
	t_vec3	lighting;
	t_vec3	light_contribution;
	int		i;

	ambient = calculate_ambient_light(record);
	lighting = (t_vec3){0, 0, 0};
	i = 0;
	while (i < g()->light_count)
	{
		light_contribution = process_single_light(record, i);
		lighting = vec3_add(lighting, light_contribution);
		++i;
	}
	return (clamp_color(vec3_add(ambient, lighting)));
}
