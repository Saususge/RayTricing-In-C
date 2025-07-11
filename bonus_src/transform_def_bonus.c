/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_def.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:44:57 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/08 15:51:24 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "rotate.h"
#include "libft.h"
#include "matrix.h"
#include <unistd.h>

void	translate(t_vec3 offset)
{
	t_gvar		*gvar;
	t_camera	*cam;
	t_light		*light;
	t_object	*obj;

	gvar = g();
	if (gvar->camera_choosed)
	{
		cam = &gvar->cam;
		cam->pos = vec3_add(cam->pos, offset);
		set_viewport();
	}
	else if (gvar->light_choosed)
	{
		light = &gvar->lights[gvar->light_index];
		light->position = vec4_add(light->position, \
			vec3_to_vec4(offset, 0.0f));
	}
	else if (gvar->choosen_object)
	{
		obj = gvar->choosen_object;
		apply_translation_to_object(obj, offset);
	}
	else
		ft_putstr_fd("No object selected to translate\n", STDERR_FILENO);
}

void	scale(float scale_factor)
{
	t_gvar	*gvar;

	gvar = g();
	if (gvar->camera_choosed)
		ft_putstr_fd("Cannot scale camera\n", STDERR_FILENO);
	else if (gvar->light_choosed)
		ft_putstr_fd("Cannot scale light\n", STDERR_FILENO);
	else if (gvar->choosen_object)
		apply_scale_to_object(gvar->choosen_object, scale_factor);
	else
		ft_putstr_fd("No object selected to scale\n", STDERR_FILENO);
}

void	rotate(t_vec3 axis, float angle)
{
	t_gvar		*gvar;
	t_camera	*cam;
	t_object	*obj;

	gvar = g();
	if (gvar->camera_choosed)
	{
		cam = &gvar->cam;
		cam->dir = vec3_normalize(
				rotate_vector_rodrigues(cam->dir, axis, angle));
		gvar->viewport.vup = vec3_normalize(
				rotate_vector_rodrigues(gvar->viewport.vup, axis, angle));
		set_viewport();
	}
	else if (gvar->light_choosed)
		ft_putstr_fd("Cannot rotate light\n", STDERR_FILENO);
	else if (gvar->choosen_object)
	{
		obj = gvar->choosen_object;
		apply_rotation_to_object(obj, vec3_normalize(axis), angle);
	}
	else
		ft_putstr_fd("No object selected to rotate\n", STDERR_FILENO);
}
