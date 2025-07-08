/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:16:30 by chakim            #+#    #+#             */
/*   Updated: 2025/07/08 15:17:57 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

int	mat_inverse(const t_mat *m, t_mat *n)
{
	float	det;
	t_mat	adj;
	float	inv_det;
	int		row;
	int		column;

	det = mat_determinant(m);
	if (fabsf(det) < EPSILON)
		return (0);
	mat_adjugate(m, &adj);
	inv_det = 1.0f / det;
	row = 0;
	while (row < 4)
	{
		column = 0;
		while (column < 4)
		{
			n->m[row][column] = adj.m[row][column] * inv_det;
			++column;
		}
		++row;
	}
	return (1);
}

// N = M ^ T
void	mat_transpose(const t_mat *m, t_mat *n)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			n->m[i][j] = m->m[j][i];
			++j;
		}
		++i;
	}
}

void	rodrigues_to_mat4(t_vec3 axis, float theta, t_mat *r)
{
	float	cos_t;
	float	sin_t;
	float	omc;

	cos_t = cosf(theta);
	sin_t = sinf(theta);
	omc = 1.0f - cos_t;
	r->m[0][0] = cos_t + axis.x * axis.x * omc;
	r->m[0][1] = axis.x * axis.y * omc - axis.z * sin_t;
	r->m[0][2] = axis.x * axis.z * omc + axis.y * sin_t;
	r->m[0][3] = 0.0f;
	r->m[1][0] = axis.y * axis.x * omc + axis.z * sin_t;
	r->m[1][1] = cos_t + axis.y * axis.y * omc;
	r->m[1][2] = axis.y * axis.z * omc - axis.x * sin_t;
	r->m[1][3] = 0.0f;
	r->m[2][0] = axis.z * axis.x * omc - axis.y * sin_t;
	r->m[2][1] = axis.z * axis.y * omc + axis.x * sin_t;
	r->m[2][2] = cos_t + axis.z * axis.z * omc;
	r->m[2][3] = 0.0f;
	r->m[3][0] = 0.0f;
	r->m[3][1] = 0.0f;
	r->m[3][2] = 0.0f;
	r->m[3][3] = 1.0f;
}
