/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:09:42 by chakim            #+#    #+#             */
/*   Updated: 2025/07/04 18:09:56 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "vector.h"
#include "rotate.h"
#include <unistd.h>

void	cylinder_rotate(t_object *this, t_vec3 axis, float angle)
{
	this->data.cylinder.axis = rotate_vector_rodrigues \
	(this->data.cylinder.axis, axis, angle);
	this->data.cylinder.p1 = vec3_add(
			this->data.cylinder.center,
			vec3_mul(this->data.cylinder.axis,
				-this->data.cylinder.height * 0.5f));
	this->data.cylinder.p2 = vec3_add(
			this->data.cylinder.center,
			vec3_mul(this->data.cylinder.axis,
				this->data.cylinder.height * 0.5f));
}
