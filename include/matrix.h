/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:14:36 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 22:22:45 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <vector.h>

typedef struct s_matrix44
{
	float	m[4][4];
}	t_mat;

typedef struct s_vec4
{
	float	v[4];
}	t_vec4;

// Homogeneous vector
t_vec4	vec3_to_vec4(t_vec3 v);
// U = M * V
void	mat_mul_vec4(const t_mat *m, const t_vec4 *v, t_vec4 *u);
// O = M * N
void	mat_mul_mat(const t_mat *m, const t_mat *n, t_mat *o);
// N = M^-1, If it can be inversed return 1, or not return 0
int		mat_inverse(const t_mat *m, t_mat *n);
float	mat_determinant(const t_mat *m);
void	mat_adjugate(const t_mat *m, t_mat *adj);
#endif