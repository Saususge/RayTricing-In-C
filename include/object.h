/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:05:15 by chakim            #+#    #+#             */
/*   Updated: 2025/04/24 13:48:03 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

typedef struct s_object		t_object;
typedef struct s_object_ops	t_object_ops;

typedef enum e_type
{
	SPHERE = 0
	
}	t_type;

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

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
	float	a;
}	t_color;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_object
{
	t_type			type;
	t_object_ops	*ops;
	void			*data;
}	t_object;

typedef struct s_hit
{
	float		t;
	t_point		point;
	t_vec3		normal;
	t_color		color;
	t_object	*object;
	int			is_front_face;
}	t_hit;

typedef struct s_object_ops
{
	int			((*intersect)(struct s_object *this, t_ray *ray,
				t_hit *hit));
	t_vec3		((*get_normal)(struct s_object * this,
			t_point * hit_point,
			t_ray * ray));
	void		(*rotate)(struct s_object *this,
			t_vec3 angle);
	void		((*translate)(struct s_object *this,
				t_vec3 offset));
	t_color		((*get_color)(struct s_object * this,
			t_point * hit_point));
	void		(*free)(struct s_object *this);
}	t_object_ops;

#endif