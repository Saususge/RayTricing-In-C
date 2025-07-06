/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:38:29 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/06 20:46:24 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static float	mat3_determinant(float m[3][3])
{
	return (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
		- m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
		+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
}

static void	mat_minor(const t_mat *m, int row, int col, float minor[3][3])
{
	int	minor_row;
	int	minor_column;
	int	m_row;
	int	m_column;

	minor_row = 0;
	m_row = -1;
	while (++m_row < 4)
	{
		if (m_row != row)
		{
			minor_column = 0;
			m_column = -1;
			while (++m_column < 4)
			{
				if (m_column != col)
				{
					minor[minor_row][minor_column] = m->m[m_row][m_column];
					++minor_column;
				}
			}
			++minor_row;
		}
	}
}

float	mat_determinant(const t_mat *m)
{
	float	det;
	float	minor[3][3];
	int		sign;
	int		column;

	det = 0.0f;
	sign = 1;
	column = 0;
	while (column < 4)
	{
		mat_minor(m, 0, column, minor);
		det += sign * m->m[0][column] * mat3_determinant(minor);
		sign = -sign;
		++column;
	}
	return (det);
}

void	mat_adjugate(const t_mat *m, t_mat *adj)
{
	static const int	sign_table[4][4] = {
	{1, -1, 1, -1},
	{-1, 1, -1, 1},
	{1, -1, 1, -1},
	{-1, 1, -1, 1}};
	float				minor[3][3];
	int					row;
	int					column;

	row = 0;
	while (row < 4)
	{
		column = 0;
		while (column < 4)
		{
			mat_minor(m, row, column, minor);
			adj->m[column][row]
				= sign_table[row][column] * mat3_determinant(minor);
			++column;
		}
		++row;
	}
}

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

#include <math.h>
void	rodrigues_to_mat4(t_vec3 axis, float theta, t_mat *r)
{
	float cos_t;
	float sin_t;
	float omc;

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

