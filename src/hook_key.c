/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:46:34 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/08 16:12:39 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "event.h"
#include "transform.h"
#include "libft.h"
#include "hit.h"
#include "mlx.h"
#include <unistd.h>

void	render_and_put(void);

static int	is_transform_keycode(int keycode)
{
	return (keycode == 'w' || keycode == 's' || keycode == 'a'
		|| keycode == 'd' || keycode == 'q' || keycode == 'e'
		|| keycode == 'p' || keycode == ';' || keycode == 'l'
		|| keycode == '\'' || keycode == 'o' || keycode == '['
		|| keycode == '=' || keycode == '-' || keycode == 't');
}

static void	transform_translate(int keycode)
{
	if (keycode == 'w')
		translate(
			vec3_mul(
				vec3_normalize(
					vec3_cross(
						g()->viewport.view_u,
						g()->viewport.view_v)), 0.1f));
	else if (keycode == 's')
		translate(
			vec3_mul(
				vec3_normalize(
					vec3_cross(
						g()->viewport.view_u,
						g()->viewport.view_v)), -0.1f));
	else if (keycode == 'a')
		translate(vec3_mul(vec3_normalize(g()->viewport.view_u), -0.1f));
	else if (keycode == 'd')
		translate(vec3_mul(vec3_normalize(g()->viewport.view_u), 0.1f));
	else if (keycode == 'q')
		translate(vec3_mul(vec3_normalize(g()->viewport.view_v), -0.1f));
	else if (keycode == 'e')
		translate(vec3_mul(vec3_normalize(g()->viewport.view_v), 0.1f));
}

static void	transform_rotate(int keycode)
{
	if (keycode == 'p')
		rotate(vec3_normalize(g()->viewport.view_u), -22.5f);
	else if (keycode == ';')
		rotate(vec3_normalize(g()->viewport.view_u), 22.5f);
	else if (keycode == 'l')
		rotate(vec3_normalize(g()->viewport.view_v), 22.5f);
	else if (keycode == '\'')
		rotate(vec3_normalize(g()->viewport.view_v), -22.5f);
	else if (keycode == 'o')
		rotate(g()->cam.dir, 22.5f);
	else if (keycode == '[')
		rotate(g()->cam.dir, -22.5f);
}

static void	transform(int keycode)
{
	if (!(g()->camera_choosed || g()->light_choosed || g()->choosen_object))
	{
		ft_putstr_fd("No object selected for transformation\n", STDERR_FILENO);
		return ;
	}
	if (keycode == 'w' || keycode == 's' || keycode == 'a'
		|| keycode == 'd' || keycode == 'q' || keycode == 'e')
		transform_translate(keycode);
	else if (keycode == 'p' || keycode == ';' || keycode == 'l'
		|| keycode == '\'' || keycode == 'o' || keycode == '[')
		transform_rotate(keycode);
	else if (keycode == '=')
		scale(1.1f);
	else if (keycode == '-')
		scale(0.9f);
	else if (keycode == 't')
	{
		g()->choosen_object->checkerboard = !g()->choosen_object->checkerboard;
		if (g()->choosen_object->checkerboard)
			ft_putstr_fd("Checkerboard enabled for selected object\n",
				STDOUT_FILENO);
		else
			ft_putstr_fd("Checkerboard disabled for selected object\n",
				STDOUT_FILENO);
	}
}

int	key_hook(int keycode, void *mlx)
{
	if (is_transform_keycode(keycode))
	{
		transform(keycode);
		render_and_put();
		return (0);
	}
	if (keycode == ESC)
		mlx_loop_end(mlx);
	else if (keycode == '1')
	{
		g()->camera_choosed = 1;
		g()->light_choosed = 0;
		ft_putstr_fd("Camera selected\n", STDOUT_FILENO);
	}
	else if (keycode == '2')
	{
		g()->camera_choosed = 0;
		if (g()->light_choosed)
			g()->light_index = (g()->light_index + 1) % g()->light_count;
		g()->light_choosed = 1;
		ft_printf("Light %d selected\n", g()->light_index + 1);
	}
	else
		ft_printf("Key %d pressed, no action defined\n", keycode);
	return (0);
}
