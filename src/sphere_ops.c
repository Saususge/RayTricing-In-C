/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:25:35 by chakim            #+#    #+#             */
/*   Updated: 2025/06/26 23:55:26 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include <unistd.h>

t_vec3	sphere_get_normal(t_object *this, t_point *hit_point, t_ray *ray)
{
	t_sphere	*sph;

	sph = (t_sphere *)this->data;
	return (vec3_normalize(vec3_sub(point_to_vec3(*hit_point), sph->center)));
}
// Sphere can be rotated, how about assign NULL instead?
void	sphere_rotate(t_object *this, t_vec3 angle)
{
	
}

void	sphere_translate(t_object *this, t_vec3 offset)
{

}

t_color	sphere_get_color(t_object *this, t_point *hit_point)
{

}

void	sphere_free(t_object *this)
{

}
