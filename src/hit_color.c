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

// #include "object.h"
// #include "hit.h"
// #define SHININESS 128.0f

// t_vec3	ambient_term(const t_object *this, t_vec4 hit_point)
// {
// 	t_vec3	amb;
// 	t_vec3	amb_intensity;

// 	amb_intensity = vec3_mul(g()->amb_light.intensity, g()->k_a);
// 	amb = vec3_hadamard(amb_intensity, this->ops->get_color(this, hit_point));
// 	return (amb);
// }

// t_vec3	diffuse_term(t_vec3 intensity, const t_hit *hit,
// 	const t_object *this, const t_light_v *light_v)
// {
// 	float	diff_dot;
// 	t_vec3	light_intensity;

// 	diff_dot = fmaxf(vec4_dot(hit->normal, light_v->l), 0.0f);
// 	light_intensity = vec3_mul(
// 		intensity, g()->k_d * diff_dot * light_v->attenuation);
// 	return (vec3_hadamard(
// 				light_intensity,
// 				this->ops->get_color(this, hit->point)));
// }

// // Assume specular color is white (255, 255, 255)
// t_vec3	specular_term(t_vec3 intensity, const t_hit *hit, const t_light_v *light_v)
// {
// 	t_vec4	view;
// 	t_vec4	reflect;
// 	float	spec_dot;
// 	float	spec_factor;
// 	t_vec3	spec_light_intensity;

// 	view = vec4_sub(vec3_to_vec4(g()->cam.pos, 1.0f), hit->point);
// 	reflect = vec4_sub(vec4_neg(light_v->l), vec4_mul(hit->normal, 2.0f * vec4_dot(vec4_neg(light_v->l), hit->normal)));
// 	spec_dot = fmaxf(vec4_dot(view, reflect) / (sqrtf(vec4_dot(view, view)) * sqrtf(vec4_dot(reflect, reflect))), 0.0f);
// 	spec_factor = powf(spec_dot, SHININESS) * g()->k_s * light_v->attenuation;
// 	return (vec3_mul(intensity, spec_factor * 255.0f));
// }

// void	calc_diff_spec(const t_hit *hit, t_vec3 *diff, t_vec3 *spec,
// 	const t_object *this)
// {
// 	int		i;
// 	t_light	*light;

// 	i = 0;
// 	while (i < g()->light_count)
// 	{
// 		light = g()->lights + i;
// 		if (is_lit(light, hit))
// 		{
// 			add_diffuse(light, hit, diff, this);
// 			add_specular(light, hit, spec);
// 		}
// 		i++;
// 	}
// }
