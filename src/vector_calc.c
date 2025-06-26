/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:52:06 by chakim            #+#    #+#             */
/*   Updated: 2025/06/26 19:01:53 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	point_distance_squared(t_point p1, t_point p2)
{
	return ((p2.x - p1.x) * (p2.x - p1.x) + \
			(p2.y - p1.y) * (p2.y - p1.y) + \
			(p2.z - p1.z) * (p2.z - p1.z));
}

float	point_distance(t_point p1, t_point p2)
{
	return (sqrtf(point_distance_squared(p1, p2)));
}

t_point	point_add_vec(t_point p, t_vec3 v)
{
	return (point_create(p.x + v.x, p.y + v.y, p.z + v.z));
}
