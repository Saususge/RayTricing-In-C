/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:03:23 by chakim            #+#    #+#             */
/*   Updated: 2025/07/03 17:57:44 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "object.h"

typedef struct s_quad_eq
{
	float	a;
	float	b;
	float	c;
	float	disc;
}	t_quad_eq;

t_object	create_sphere(t_point center, float radius, t_vec3 color);
int			sphere_intersect(const t_object *this,
				const t_ray *ray, t_hit *hit, t_t_bound bound);
int			shpere_shadow_intersect(const t_object *this,
				const t_ray *ray, t_t_bound bound);
void		sphere_rotate(t_object *this, t_vec3 angle);
void		sphere_translate(t_object *this, t_vec3 offset);
t_vec3		sphere_get_normal(const t_object *this, const t_point *hit_point);
void		calculate_sphere_equation(t_quad_eq *eq, \
	const t_sphere *sph, const t_ray *ray);
int			hit_shadow(const t_ray *ray, float t_min, float t_max);
void		set_hit_geometry(t_hit *hit, float t, \
	const t_ray *ray, const t_object *this);
t_vec3		calc_ambient(const t_object *this);
t_vec3		get_light_dir(const t_light *light, const t_hit *hit);
float		get_light_distance(const t_light *light, const t_hit *hit);
int			is_lit(const t_light *light, const t_hit *hit);
void		add_diffuse(const t_light *light, \
	const t_hit *hit, t_vec3 *diff, const t_object *this);
float		calc_spec_factor(const t_light *light, \
	const t_hit *hit, t_vec3 reflect_dir);
void		add_specular(const t_light *light, const t_hit *hit, t_vec3 *spec);
void		calc_diff_spec(const t_hit *hit, \
	t_vec3 *diff, t_vec3 *spec, const t_object *this);
t_vec3		clamp_color_vec3(t_vec3 color);
void		populate_hit_record(t_hit *hit, \
	float t, const t_ray *ray, const t_object *this);
void		sphere_scale(t_object *this, float scale);
#endif
