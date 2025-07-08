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

# define K_AMBIENT 0.2f
# define K_DIFFUSE 1.0f
# define K_SPECULAR 1.0f
# define SHININESS 64.0f


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
int		hit_ray(const t_ray *ray_world, t_interval bound_world, t_intersect *intersect_record, t_vec3 *color);
int		hit_shadow_ray(const t_ray *shadow_ray_world, t_interval bound_world);
int		shoot_ray_from_viewport(int x, int y, t_object **obj, t_vec3 *color);
t_vec3	calculate_ambient_light(const t_intersect *record);
float	calculate_light_distance(t_vec4 light_pos, t_vec4 point);
t_vec4	calculate_light_direction(t_vec4 light_pos, t_vec4 point);
t_vec3	calculate_diffuse_light(const t_intersect *record, t_vec4 light_dir, 
							float attenuation, t_vec3 light_intensity);
t_vec3	calculate_specular_light(const t_intersect *record, t_vec4 light_dir, 
							float attenuation, t_vec3 light_intensity);
int		is_in_shadow(const t_intersect *record, int light_idx);
float	calculate_attenuation(const t_intersect *record, int light_idx);
t_vec3	process_single_light(const t_intersect *record, int light_idx);
t_vec3	get_color(const t_intersect *record);
t_vec3	clamp_color(t_vec3 color);
#endif
