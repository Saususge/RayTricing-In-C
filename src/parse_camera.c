/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/30 01:38:05 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int	parse_camera(void)
{
	t_camera	camera;
	char		*pos_str;
	char		*orient_str;
	char		*fov_str;
	float		mag;

	pos_str = ft_strtok(NULL, " \t\n");
	orient_str = ft_strtok(NULL, " \t\n");
	fov_str = ft_strtok(NULL, " \t\n");
	if (parse_vec3(pos_str, &camera.position))
		return (1);
	if (parse_vec3(orient_str, &camera.orientation))
		return (1);
	mag = vec3_length(camera.orientation);
	if (mag < 1.0f - EPSILON || mag > 1.0f + EPSILON)
		return (1);
	if (parse_float(fov_str, &camera.fov)
		|| camera.fov < 0.0f || camera.fov > 180.0f)
		return (1);
	g_camera = camera;
	return (0);
}
