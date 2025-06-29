/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:25:35 by chakim            #+#    #+#             */
/*   Updated: 2025/06/30 01:56:11 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include <unistd.h>

t_vec3	sphere_get_normal(t_object *this, t_point *hit_point)
{
	return (vec3_normalize(vec3_sub(*hit_point, this->data.sphere.center)));
}

void	sphere_translate(t_object *this, t_vec3 offset)
{
	this->data.sphere.center = vec3_add(this->data.sphere.center, offset);
}

t_color	sphere_get_color(t_object *this)
{
	return (this->data.sphere.color);
}
