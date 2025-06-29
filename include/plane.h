/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:08:13 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 02:09:52 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "object.h"
# include "vector.h"

t_object	 create_plane(t_point point, t_vec3 normal, t_color color);
int	plane_intersect(const t_object *this, const t_ray *ray, t_hit *hit, t_t_bound bound);
int	plane_shadow_intersect(const t_object *this, const t_ray *ray, t_t_bound bound);
t_vec3	plane_get_normal(t_object *this, t_point *hit_point);
void	plane_translate(t_object *this, t_vec3 offset);
void	plane_rotate(t_object *this, t_vec3 angle);
t_color	plane_get_color(t_object *this);
#endif