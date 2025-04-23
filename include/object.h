/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:05:15 by chakim            #+#    #+#             */
/*   Updated: 2025/04/23 18:00:59 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

typedef enum e_type
{
	SPHERE = 0
}	t_type;

typedef struct s_object_ops
{
	int			((*intersect)(struct s_object *this, t_ray *ray, \
		t_hit *hit));
	t_vec		((*get_normal)(struct s_object * this,
			t_point * hit_point,
			t_ray * ray));
	void		(*rotate)(struct s_object *this,
			t_vec angle);
	void		((*translate)(struct s_object *this,
				t_vec offset));
	t_color		((*get_color)(struct s_object * this,
			t_point * hit_point));
	void		(*free)(struct s_object *this);
}	t_object_ops;
typedef struct s_object
{
	t_type			type;
	t_object_ops	*ops;
	void			*data;
}	t_object;

#endif