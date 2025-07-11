/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_def_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:00:00 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/08 00:00:00 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"
#include "object.h"

t_vec3	clamp_color(t_vec3 color)
{
	color = vec3_max(color, (t_vec3){0, 0, 0});
	color = vec3_min(color, (t_vec3){255, 255, 255});
	return (color);
}

t_vec3	calculate_ambient_light(const t_intersect *record)
{
	t_vec3	ambient;
	t_vec3	color;

	color = record->obj->ops->get_color(record);
	ambient = vec3_hadamard(vec3_mul(g()->amb_light.intensity, \
	K_AMBIENT), color);
	return (ambient);
}

float	calculate_light_distance(t_vec4 light_pos, t_vec4 point)
{
	t_vec4	light_vector;
	float	distance;

	light_vector = vec4_sub(light_pos, point);
	distance = sqrtf(vec4_dot(light_vector, light_vector));
	return (distance);
}

t_vec4	calculate_light_direction(t_vec4 light_pos, t_vec4 point)
{
	t_vec4	light_vector;
	float	distance;

	light_vector = vec4_sub(light_pos, point);
	distance = sqrtf(vec4_dot(light_vector, light_vector));
	return (vec4_mul(light_vector, 1.0f / distance));
}

t_vec3	calculate_diffuse_light(const t_intersect *record, t_vec4 light_dir, \
	float attenuation, t_vec3 light_intensity)
{
	t_vec3	diffuse;
	t_vec3	color;
	float	diffusion_dot;
	t_vec3	diffusion_light_intensity;

	color = record->obj->ops->get_color(record);
	diffusion_dot = fmaxf(vec4_dot(record->n_world, light_dir), 0.0f);
	diffusion_light_intensity = vec3_mul(light_intensity, \
		K_DIFFUSE * diffusion_dot * attenuation);
	diffuse = vec3_hadamard(diffusion_light_intensity, color);
	return (diffuse);
}
