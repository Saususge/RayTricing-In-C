/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:25 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 17:20:25 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H
# include "object.h"

typedef struct s_light_v
{
	t_vec4	l;
	float	distance_sq;
	float	attenuation;
}	t_light_v;

t_vec3	ambient_term(const t_object *this, t_vec4 hit_point);
void	add_diffuse(const t_light *light, const t_hit *hit,
			t_vec3 *diff, const t_object *this);
float	calc_spec_factor(const t_light *light,
			const t_hit *hit, t_vec3 reflect_dir);
void	add_specular(const t_light *light, const t_hit *hit, t_vec3 *spec);
void	calc_diff_spec(const t_hit *hit, t_vec3 *diff,
			t_vec3 *spec, const t_object *this);
t_vec3	clamp_color_vec3(t_vec3 color);
void	populate_hit_record(t_hit *hit, float t,
			const t_ray *ray, const t_object *this);
t_vec4	get_light_dir(const t_light *light, const t_hit *hit);
int		is_lit(const t_light *light, const t_hit *hit);
int		hit_objects(const t_ray *ray, float t_min, float t_max, t_hit *hit);
int		hit_shadow(const t_ray *ray, float t_min, float t_max);
int		shoot_ray_from_viewport(int x, int y, t_hit *hit);
#endif
