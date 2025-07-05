/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:38:29 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/05 15:37:40 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_vec4	vec3_to_vec4(t_vec3 v, float w)
{
	return ((t_vec4){{v.x, v.y, v.z, w}});
}

t_vec4	mat_mul_vec4(const t_mat *m, t_vec4 v)
{
	t_vec4	u;
	int	row;

	row = 0;
	while (row < 4)
	{
		u.v[row]
			= m->m[row][0] * v.v[0]
			+ m->m[row][1] * v.v[1]
			+ m->m[row][2] * v.v[2]
			+ m->m[row][3] * v.v[3];
		++row;
	}
	return (u);
}

void	mat_mul_mat(const t_mat *m, const t_mat *n, t_mat *o)
{
	int	row;
	int	column;

	row = 0;
	while (row < 4)
	{
		column = 0;
		while (column < 4)
		{
			o->m[row][column] = m->m[row][0] * n->m[0][column]
				+ m->m[row][1] * n->m[1][column]
				+ m->m[row][2] * n->m[2][column]
				+ m->m[row][3] * n->m[3][column];
			++column;
		}
		++row;
	}
}
