/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:36:03 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 14:04:34 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "object.h"
# include "vector.h"
# include "sphere.h"

t_object	create_cone(t_point center, t_vec3 axis, float radius, float height, t_vec3 color);
int			cone_intersect(const t_object *this, const t_ray *ray, t_hit *hit, t_t_bound bound);
int			cone_shadow_intersect(const t_object *this, const t_ray *ray, t_t_bound bound);
t_vec3		cone_get_normal(const t_object *this, t_point *hit_point);
void 		cone_translate(t_object *this, t_vec3 offset);
void 		cone_rotate(t_object *this, t_vec3 angle);

#endif
