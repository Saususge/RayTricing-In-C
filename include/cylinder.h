/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/07/08 14:50:35 by chakim           ###   ########.fr       */
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

typedef struct s_cap_uv_data
{
	t_point	p;
	t_point	center;
	t_vec3	axis;
	float	radius;
}	t_cap_uv_data;

t_object	create_cylinder(struct s_cyl_data data);
int			cylinder_intersect(const t_object *obj, const t_ray *ray_world, t_intersect *record, t_interval t_bound);
t_vec3		cylinder_get_color(const t_intersect *record);

// cylinder utility functions
int			check_cylinder_height(const t_ray *ray, float t);
int			intersect_lateral(const t_ray *local_ray, t_interval bound, float *t);
int			intersect_cap(const t_ray *local_ray, t_interval bound, float *t);
t_vec3		get_cylinder_u_axis(t_vec3 axis);
void		calculate_cylinder_uv_dirs(t_vec3 axis,
				t_vec3 *u_dir, t_vec3 *v_dir);
// void		cylinder_get_uv(t_point p,
// 				const t_cylinder *cy, float *u, float *v);
#endif