/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 21:03:17 by wchoe            ###   ########.fr       */
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

struct s_cyl_parse_data
{
	t_point	center;
	t_vec3	orient;
	float	diameter;
	float	height;
	t_vec3	color;
	char	*center_str;
	char	*orient_str;
	char	*diam_str;
	char	*height_str;
	char	*color_str;
};

typedef struct s_cap_uv_data
{
	t_point	p;
	t_point	center;
	t_vec3	axis;
	float	radius;
}	t_cap_uv_data;

t_object	create_cylinder(struct s_cyl_data data);
int			cylinder_intersect(const t_object *obj, \
	const t_ray *ray_world, t_intersect *record, t_interval t_bound);
t_vec3		cylinder_get_color(const t_intersect *record);

// cylinder utility functions
int			check_cylinder_height(const t_ray *ray, float t);
int			intersect_lateral(const t_ray *local_ray, \
	t_interval bound, float *t);
int			intersect_cap(const t_ray *local_ray, t_interval bound, float *t);
t_vec3		get_cylinder_u_axis(t_vec3 axis);
t_vec4		get_bumped_normal_cylinder(t_vec4 p_local);
#endif