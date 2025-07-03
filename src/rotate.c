/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:09:44 by chakim            #+#    #+#             */
/*   Updated: 2025/07/03 20:30:41 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotate.h"

#define DEGREE_TO_RADIAN ((float)M_PI / 180.0f)

static t_vec3	rotate(t_vec3 target, t_rotation rot)
{
	t_rot_res	res;

	res.x1 = target.x * rot.cos_z - target.y * rot.sin_z;
	res.y1 = target.x * rot.sin_z + target.y * rot.cos_z;
	res.z1 = target.z;
	res.x2 = res.x1 * rot.cos_y + res.z1 * rot.sin_y;
	res.y2 = res.y1;
	res.z2 = -res.x1 * rot.sin_y + res.z1 * rot.cos_y;
	res.x3 = res.x2;
	res.y3 = res.y2 * rot.cos_x - res.z2 * rot.sin_x;
	res.z3 = res.y2 * rot.sin_x + res.z2 * rot.cos_x;
	return ((t_vec3){res.x3, res.y3, res.z3});
}

static void	init_rotation(t_rotation *rot, t_vec3 *angle)
{
	float	degree_to_radian;

	degree_to_radian = 3.1415927f / 180.0f;
	rot->cos_x = cosf(angle->x * degree_to_radian);
	rot->cos_y = cosf(angle->y * degree_to_radian);
	rot->cos_z = cosf(angle->z * degree_to_radian);
	rot->sin_x = sinf(angle->x * degree_to_radian);
	rot->sin_y = sinf(angle->y * degree_to_radian);
	rot->sin_z = sinf(angle->z * degree_to_radian);
}

t_vec3	rotate_vector(t_vec3 target, t_vec3 angle)
{
	t_rotation	rot;

	init_rotation(&rot, &angle);
	return (rotate(target, rot));
}

// axis must be normalized
t_vec3	rotate_vector_rodrigues(t_vec3 target, t_vec3 axis, float angle)
{
	float	cos_theta;
	float	sin_theta;
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;

	cos_theta = cosf(angle * DEGREE_TO_RADIAN);
	sin_theta = sinf(angle * DEGREE_TO_RADIAN);
	term1 = vec3_mul(target, cos_theta);
	term2 = vec3_mul(vec3_cross(axis, target), sin_theta);
	term3 = vec3_mul(axis, vec3_dot(axis, target) * (1.0f - cos_theta));
	return (vec3_add(vec3_add(term1, term2), term3));
}
