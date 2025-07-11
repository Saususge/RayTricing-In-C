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
