/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/07/03 17:57:20 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "object.h"
# include "vector.h"
# include "sphere.h"
# include <math.h>

struct s_cyl_data
{
	t_point	center;
	t_vec3	axis;
	float	radius;
	float	height;
	t_vec3	color;
};

t_object	create_cylinder(struct s_cyl_data data);
void		calculate_cylinder_equation(t_quad_eq *eq, \
	const t_cylinder *cyl, const t_ray *ray);
int			check_in_circle(const t_cylinder *cyl, \
	const t_ray *ray, t_point cap_center, float t);
int			intersect_cap(const t_cylinder *cyl, \
	const t_ray *ray, float *t, t_t_bound bound);
int			check_height(const t_cylinder *cyl, t_point hit_point);
int			intersect_lateral(const t_cylinder *cyl, \
	const t_ray *ray, float *t, t_t_bound bound);
int			cylinder_intersect(
				const t_object *this,
				const t_ray *ray, t_hit *hit, t_t_bound bound);
int			cylinder_shadow_intersect(
				const t_object *this, const t_ray *ray, t_t_bound bound);
t_vec3		cylinder_get_normal(const t_object *this, const t_point *hit_point);
void		cylinder_translate(t_object *this, t_vec3 offset);
void		cylinder_rotate(t_object *this, t_vec3 angle);
void		cylinder_scale(t_object *this, float scale);
#endif