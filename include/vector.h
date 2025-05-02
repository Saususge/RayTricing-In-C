/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:25:20 by chakim            #+#    #+#             */
/*   Updated: 2025/05/02 17:45:24 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

t_vec3	vec3_create(float x, float y, float z);

#endif