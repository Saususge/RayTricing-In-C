/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:08:13 by chakim            #+#    #+#             */
/*   Updated: 2025/05/26 14:12:27 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "object.h"
# include "vector.h"
# include "test.h"

typedef struct s_plane
{
	t_point	point;
	t_vec3	normal;
	t_vec3	color;
}	t_plane;

t_object	*create_plane(t_point point, t_vec3 normal, t_vec3 color);
int			plane_intersect(t_object *this, t_ray *ray, t_hit *hit);

#endif