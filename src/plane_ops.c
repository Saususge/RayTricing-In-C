/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:23:09 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 18:23:48 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include "vector.h"
#include "rotate.h"
#include <stdlib.h>
#include <stdio.h>

t_vec3	plane_get_normal(const t_object *this, const t_point *hit_point)
{
	(void)hit_point;
	return (this->data.plane.normal);
}

void	plane_translate(t_object *this, t_vec3 offset)
{
	this->data.plane.point = vec3_add(this->data.plane.point, offset);
}

void	plane_rotate(t_object *this, t_vec3 axis, float angle)
{
	this->data.plane.normal = rotate_vector_rodrigues(
			this->data.plane.normal, axis, angle);
}

void	plane_scale(t_object *this, float scale)
{
	(void)this;
	(void)scale;
	printf("Scaling a plane is not applicable.\n");
}
