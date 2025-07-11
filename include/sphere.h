/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:03:23 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 22:02:32 by wchoe            ###   ########.fr       */
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
int			sphere_intersect(const t_object *obj, const t_ray *ray_world, \
	t_intersect *intersect_record, t_interval t_world_bound);
t_vec4		sphere_get_normal(t_vec4 hit_point);
void		calculate_sphere_equation(t_quad_eq *eq, const t_ray *ray);
t_vec3		sphere_get_color(const t_intersect *record);
void		get_uv_sphere(t_vec4 p_local, float *u, float *v);
t_vec4		get_bumpmap_normal(float u, float v);
t_vec4		get_bumped_normal_sphere(t_vec4	p_local);
t_vec3		sphere_get_color(const t_intersect *record);
#endif
