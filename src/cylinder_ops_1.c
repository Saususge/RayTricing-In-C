/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_ops_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:11:31 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 18:11:43 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

void	cylinder_scale(t_object *this, float scale)
{
	this->data.cylinder.radius *= scale;
	this->data.cylinder.height *= scale;
	this->data.cylinder.p1 = vec3_add(
			this->data.cylinder.center,
			vec3_mul(this->data.cylinder.axis,
				-this->data.cylinder.height * 0.5f));
	this->data.cylinder.p2 = vec3_add(
			this->data.cylinder.center,
			vec3_mul(this->data.cylinder.axis,
				this->data.cylinder.height * 0.5f));
}
