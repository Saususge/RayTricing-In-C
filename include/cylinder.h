/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:56:47 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 04:18:52 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "object.h"
# include "vector.h"
# include "sphere.h"
# include <math.h>

t_object	create_cylinder(t_point p1, t_point p2, float radius, t_vec3 color);
int			cylinder_intersect(const t_object *this, const t_ray *ray, t_hit *hit, t_t_bound bound);
int			cylinder_shadow_intersect(const t_object *this, const t_ray *ray, t_t_bound bound);
t_vec3		cylinder_get_normal(const t_object *this, t_point *hit_point);

#endif