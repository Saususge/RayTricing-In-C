/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:36:03 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 21:31:10 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "object.h"
# include "vector.h"
# include "sphere.h"

struct s_cone_data
{
	t_point	center;
	t_vec3	axis;
	float	radius;
	float	height;
	t_vec3	color;
};

typedef struct s_cone_cap_data
{
	t_point	p;
	t_point	cap_center;
	t_vec3	axis;
	float	radius;
}	t_cone_cap_data;

typedef struct s_quad_eq_cone
{
	float	a;
	float	b;
	float	c;
	float	disc;
}	t_quad_eq_c;

struct s_cone_parse_data
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

t_object	create_cone(struct s_cone_data data);

int			cone_intersect(const t_object *obj, const t_ray *ray_world, \
				t_intersect *intersect_record, t_interval t_world_bound);
int			cone_lateral_intersect(const t_ray *ray, \
	float *t, t_interval t_bound);
int			cone_intersect_cap(const t_ray *ray, float *t, t_interval t_bound);
t_vec4		cone_get_normal(t_vec4 p_local);
t_vec3		cone_get_color(const t_intersect *record);
t_vec4		get_bumped_normal_cone(t_vec4 p_local);
#endif
