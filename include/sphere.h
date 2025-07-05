/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:03:23 by chakim            #+#    #+#             */
/*   Updated: 2025/07/05 14:05:24 by wchoe            ###   ########.fr       */
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
				const t_ray *ray, t_hit *hit, t_interval bound);
int			shpere_shadow_intersect(const t_object *this,
				const t_ray *ray, t_interval bound);
t_vec4		sphere_get_normal(const t_object *this, t_vec4 hit_point);
void		calculate_sphere_equation(t_quad_eq *eq, const t_ray *ray);
t_vec3		sphere_get_color(const t_object *obj, t_vec4 hit_point);
#endif
