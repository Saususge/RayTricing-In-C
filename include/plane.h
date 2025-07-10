/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:08:13 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 20:34:35 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "object.h"
# include "vector.h"

t_object	create_plane(t_point point, t_vec3 normal, t_vec3 color);
int			plane_intersect(const t_object *obj, \
	const t_ray *ray_world, t_intersect *intersect_record, \
	t_interval t_world_bound);
t_vec4		plane_get_normal(void);
t_vec3		plane_get_color(const t_intersect *record);
void		init_plane_basic(t_object *pl, t_vec3 color);
void		init_transform_matrix(t_object *pl, t_point point);
void		init_rotation_matrix(t_object *pl, t_vec3 normal);
t_vec4		get_bumped_normal_plane(t_vec4	p_local);
#endif