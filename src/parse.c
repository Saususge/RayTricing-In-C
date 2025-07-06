/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/06 14:34:09 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static int	dispatch_parse(const char *id)
{
	if (!ft_strcmp(id, "A"))
		return (parse_ambient());
	if (!ft_strcmp(id, "C"))
		return (parse_camera());
	if (!ft_strcmp(id, "L"))
		return (parse_light());
	if (!ft_strcmp(id, "sp"))
		return (parse_sphere());
	// if (!ft_strcmp(id, "pl"))
	// 	return (parse_plane());
	// if (!ft_strcmp(id, "cy"))
	// 	return (parse_cylinder());
	// if (!ft_strcmp(id, "co"))
	// 	return (parse_cone());
	return (1);
}

// Main parse function
int	parse(int fd)
{
	char	*line;
	char	*id;

	line = get_next_line(fd);
	while (line)
	{
		id = ft_strtok(line, " \t\n");
		if (id)
		{
			if (dispatch_parse(id))
			{
				free(line);
				return (1);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

void	move_cam_light_to_local(int light_idx, int obj_idx)
{
	t_gvar		*gvar;
	t_camera	*cam;
	t_light		*light;
	t_object	*obj;

	gvar = g();
	cam = &gvar->cam;
	light = gvar->lights + light_idx;
	obj = gvar->objects + obj_idx;
	obj->local_cam_pos = mat_mul_vec4(&obj->m_inv, vec3_to_vec4(cam->pos, 1.0f));
	obj->local_light_pos[light_idx] = mat_mul_vec4(&obj->m_inv, light->position);
}
