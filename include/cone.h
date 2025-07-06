/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:36:03 by chakim            #+#    #+#             */
/*   Updated: 2025/07/06 13:54:55 by wchoe            ###   ########.fr       */
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

t_object	create_cone(struct s_cone_data data);
int			cone_intersect(
				const t_object *this,
				const t_ray *ray, t_hit *hit, t_interval bound);
int			cone_shadow_intersect(
				const t_object *this, const t_ray *ray, t_interval bound);
t_vec3		cone_get_normal(const t_object *this, const t_point *hit_point);
void		cone_translate(t_object *this, t_vec3 offset);
void		cone_rotate(t_object *this, t_vec3 axis, float angle);
// void		calculate_cone_equation(
// 				t_quad_eq *eq,
// 				const t_cone *cone,
// 				const t_ray *ray);
// int			cone_check_height(
// 				const t_cone *cone,
// 				t_point hit_point);
// int			cone_intersect_cap(
// 				const t_cone *cone,
// 				const t_ray *ray,
// 				float *t,
// 				t_interval bound);
// int			cone_lateral_intersect(
// 				const t_cone *cone,
// 				const t_ray *ray,
// 				float *t,
// 				t_interval bound);
void		cone_scale(t_object *this, float scale);
t_vec3		cone_get_color(const t_object *obj, t_point hit_point);
t_vec3		get_cone_u_axis(t_vec3 axis);
void		calculate_cone_uv_dirs(t_vec3 axis, t_vec3 *u_dir, t_vec3 *v_dir);
// void		cone_lateral_uv(t_point p, const t_cone *cone, float *u, float *v);
void		cone_cap_uv(t_cone_cap_data data, float *u, float *v);

#endif
