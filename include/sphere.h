/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:03:23 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 02:37:31 by wchoe            ###   ########.fr       */
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
int			sphere_intersect(const t_object *this, const t_ray *ray, t_hit *hit, t_t_bound bound);
int			shpere_shadow_intersect(const t_object *this, const t_ray *ray, t_t_bound bound);
void		sphere_rotate(t_object *this, t_vec3 angle);
void		sphere_translate(t_object *this, t_vec3 offset);
t_vec3		sphere_get_normal(const t_object *this, t_point *hit_point);


#endif
