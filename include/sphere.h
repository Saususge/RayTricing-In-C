/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:03:23 by chakim            #+#    #+#             */
/*   Updated: 2025/06/26 23:23:19 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "object.h"
# include "test.h"

typedef struct s_quad_eq
{
	float	a;
	float	b;
	float	c;
	float	disc;
}	t_quad_eq;

typedef struct s_sphere
{
	t_point	center;
	float	radius;
	t_color	color;
}	t_sphere;

t_object	*create_sphere(t_point center, float radius, t_color color);
int			sphere_intersect(t_object *this, t_ray *ray, t_hit *hit);
t_vec3		sphere_get_normal(t_object *this, t_point *hit_point, t_ray *ray);
void		sphere_rotate(t_object *this, t_vec3 angle);
void		sphere_translate(t_object *this, t_vec3 offset);
t_color		sphere_get_color(t_object *this, t_point *hit_point);
void		sphere_free(t_object *this);

#endif
