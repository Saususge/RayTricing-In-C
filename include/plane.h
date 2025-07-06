/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:08:13 by chakim            #+#    #+#             */
/*   Updated: 2025/07/06 20:51:15 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "object.h"
# include "vector.h"

t_object	create_plane(t_point point, t_vec3 normal, t_vec3 color);
int			plane_intersect(const t_object *obj, const t_ray *ray_world, t_intersect *intersect_record, t_interval t_world_bound);
t_vec4		plane_get_normal(const t_object *this, t_vec4 hit_point);
t_vec3		plane_get_color(const t_intersect *record);
#endif