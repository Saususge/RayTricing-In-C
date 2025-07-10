/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_reflect_refract.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:06:09 by chakim            #+#    #+#             */
/*   Updated: 2025/07/10 20:21:05 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vec3	vec3_reflect(t_vec3 v, t_vec3 normal)
{
	return (vec3_sub(v, vec3_mul(normal, 2.0f * vec3_dot(v, normal))));
}

t_vec3	vec3_refract(t_vec3 v, t_vec3 normal, float refraction_ratio)
{
	t_vec3	l_term;
	t_vec3	n_term;
	float	cos_incident;
	float	cos_refracted_sq;

	cos_incident = -vec3_dot(v, normal);
	cos_refracted_sq = 1.0f - refraction_ratio * \
refraction_ratio * (1.0f - cos_incident * cos_incident);
	if (cos_refracted_sq < 0.0f)
		return (vec3_reflect(v, normal));
	else
	{
		l_term = vec3_mul(normal, refraction_ratio * \
cos_incident - sqrtf(1 - refraction_ratio * refraction_ratio * \
	(1 - cos_incident * cos_incident)));
		n_term = vec3_mul(v, refraction_ratio);
		return (vec3_add(n_term, l_term));
	}
}
