/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:36:03 by chakim            #+#    #+#             */
/*   Updated: 2025/07/01 13:21:09 by chakim           ###   ########.fr       */
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

t_object	create_cone(struct s_cone_data data);
int			cone_intersect(
				const t_object *this,
				const t_ray *ray, t_hit *hit, t_t_bound bound);
int			cone_shadow_intersect(
				const t_object *this, const t_ray *ray, t_t_bound bound);
t_vec3		cone_get_normal(const t_object *this, const t_point *hit_point);
void		cone_translate(t_object *this, t_vec3 offset);
void		cone_rotate(t_object *this, t_vec3 angle);
void		calculate_cone_equation(
				t_quad_eq *eq,
				const t_cone *cone,
				const t_ray *ray);
int			cone_check_height(
				const t_cone *cone,
				t_point hit_point);
int			cone_intersect_cap(
				const t_cone *cone,
				const t_ray *ray,
				float *t,
				t_t_bound bound);
int			cone_lateral_intersect(
				const t_cone *cone,
				const t_ray *ray,
				float *t,
				t_t_bound bound);
#endif
