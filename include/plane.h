/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:08:13 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 01:01:17 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "object.h"
# include "vector.h"

t_object	create_plane(t_point point, t_vec3 normal, t_color color);
int			plane_intersect(t_object *this, t_ray *ray, t_hit *hit);
t_vec3		plane_get_normal(t_object *this, t_point *hit_point, t_ray *ray);
void		plane_translate(t_object *this, t_vec3 offset);
void		plane_rotate(t_object *this, t_vec3 angle);
t_color		plane_get_color(t_object *this, t_point *hit_point);

#endif