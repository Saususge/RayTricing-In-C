/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:49:19 by chakim            #+#    #+#             */
/*   Updated: 2025/07/08 17:19:23 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "rotate.h"
#include "libft.h"
#include "matrix.h"
#include <unistd.h>

void	compute_final_matrices(t_object *obj)
{
	t_mat	temp;

	mat_mul_mat(&obj->r, &obj->s, &temp);
	mat_mul_mat(&obj->t, &temp, &obj->m);
	mat_inverse(&obj->m, &obj->m_inv);
	mat_transpose(&obj->m_inv, &obj->n);
}

void	apply_translation_to_object(t_object *obj, t_vec3 offset)
{
	obj->t.m[0][3] += offset.x;
	obj->t.m[1][3] += offset.y;
	obj->t.m[2][3] += offset.z;
	compute_final_matrices(obj);
}

void	apply_scale_to_object(t_object *obj, float scale_factor)
{
	if (scale_factor < 1.0f && obj->s.m[0][0] <= 0.08f)
		return ;
	obj->s.m[0][0] *= scale_factor;
	obj->s.m[1][1] *= scale_factor;
	obj->s.m[2][2] *= scale_factor;
	compute_final_matrices(obj);
}

void	apply_rotation_to_object(t_object *obj, t_vec3 axis, float angle)
{
	t_mat	rotation_matrix;
	t_mat	new_rotation;

	rodrigues_to_mat4(axis, angle * M_PI / 180.0f, &rotation_matrix);
	mat_mul_mat(&rotation_matrix, &obj->r, &new_rotation);
	obj->r = new_rotation;
	compute_final_matrices(obj);
}
