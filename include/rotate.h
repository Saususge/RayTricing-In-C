/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:31:47 by chakim            #+#    #+#             */
/*   Updated: 2025/06/26 23:48:44 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATE_H
# define ROTATE_H
# define _USE_MATH_DEFINES
# include "object.h"
# include "vector.h"
# include <math.h>

typedef struct s_rotation
{
	float	sin_x;
	float	cos_x;
	float	sin_y;
	float	cos_y;
	float	sin_z;
	float	cos_z;
}	t_rotation;

typedef struct s_rot_res
{
	float	x1;
	float	x2;
	float	x3;
	float	y1;
	float	y2;
	float	y3;
	float	z1;
	float	z2;
	float	z3;
}	t_rot_res;

t_vec3	rotate_vector(t_vec3 target, t_vec3 angle);
#endif