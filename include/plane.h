/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:08:13 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 21:39:05 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "object.h"
# include "vector.h"

t_object	create_plane(t_point point, t_vec3 normal, t_vec3 color);
int			plane_intersect(
				const t_object *this,
				const t_ray *ray, t_hit *hit, t_t_bound bound);
int			plane_shadow_intersect(
				const t_object *this, const t_ray *ray, t_t_bound bound);
t_vec3		plane_get_normal(const t_object *this, const t_point *hit_point);
t_vec3		plane_get_color(const t_object *obj, t_point hit_point);
#endif