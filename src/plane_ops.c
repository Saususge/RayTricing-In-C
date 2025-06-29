/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:23:09 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 02:09:41 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "vector.h"
#include "rotate.h"
#include <stdlib.h>

t_vec3	plane_get_normal(t_object *this, t_point *hit_point)
{
	(void)hit_point;
	return (vec3_normalize(this->data.plane.normal));
}

// void	plane_translate(t_object *this, t_vec3 offset)
// {
// 	this->data.plane.point = vec3_add(this->data.plane.point, offset);
// }

// void	plane_rotate(t_object *this, t_vec3 angle)
// {
// 	this->data.plane.normal = \
// 	(t_vec3)rotate_vector(this->data.plane.normal, angle);
// }

t_color	plane_get_color(t_object *this)
{
	return (this->data.plane.color);
}
