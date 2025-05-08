/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:48:33 by chakim            #+#    #+#             */
/*   Updated: 2025/05/08 16:50:24 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	point_to_vec3(t_point p)
{
	t_vec3	vec;

	vec.x = p.x;
	vec.y = p.y;
	vec.z = p.z;

	return (vec);
}

t_point	vec3_to_point(t_vec3 v)
{
	t_point	p;

	p.x = v.x;
	p.y = v.y;
	p.z = v.z;

	return (p);
}
