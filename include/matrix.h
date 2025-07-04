/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:14:36 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 21:34:20 by wchoe            ###   ########.fr       */
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
extern inline 		t_vec4	vec3_to_vec4(t_vec3 v);
// U = M * V
extern inline void	mat_mul_vec4(const t_mat *m, const t_vec4 *v, t_vec4 *u);
// O = M * N
extern inline void	mat_mul_mat(const t_mat *m, const t_mat *n, const t_mat *o);
// N = M^-1
extern inline void	mat_inverse(const t_mat *m, const t_mat *n);
#endif