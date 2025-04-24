/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:56:33 by chakim            #+#    #+#             */
/*   Updated: 2025/04/24 13:28:07 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "mlx.h"
#include "object.h"

void	init_test(t_scene *scene)
{
	scene->cam.pos = (t_vec3){0, 0, -20};
	scene->cam.dir = (t_vec3){0, 0, 1};
	scene->cam.fov = 70;
	scene->sp.center = (t_vec3){0, 0, 20};
	scene->sp.radius = 10;
	scene->sp.color = (t_vec3){255, 0, 0};
}
