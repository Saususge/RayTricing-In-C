/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:25:35 by chakim            #+#    #+#             */
/*   Updated: 2025/07/01 09:17:52 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "vector.h"
#include <unistd.h>
#include <stdio.h>

void	sphere_translate(t_object *this, t_vec3 offset)
{
	this->data.sphere.center = vec3_add(this->data.sphere.center, offset);
}

void	sphere_rotate(t_object *this, t_vec3 angle)
{
	(void)this;
	(void)angle;
	printf("Sphere cannot be rotated.\n");
}
