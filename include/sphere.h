/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:03:23 by chakim            #+#    #+#             */
/*   Updated: 2025/05/17 13:54:20 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "object.h"
# include "test.h"

t_object	*create_sphere(t_point center);
int			sphere_intersect(t_object *this, t_ray *ray, t_hit *hit);

#endif
