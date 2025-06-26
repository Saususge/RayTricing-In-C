/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/26 21:43:03 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Classifier and dispatcher
static int	dispatch_parse(const char *id, int fd)
{
	(void)fd;
	if (!ft_strcmp(id, "A"))
		return (parse_ambient());
	if (!ft_strcmp(id, "C"))
		return (parse_camera());
	if (!ft_strcmp(id, "L"))
		return (parse_light());
	if (!ft_strcmp(id, "sp"))
		return (parse_sphere());
	if (!ft_strcmp(id, "pl"))
		return (parse_plane());
	if (!ft_strcmp(id, "cy"))
		return (parse_cylinder());
	return (1);
}

// Helper to parse a vector (e.g. "x,y,z")
static int parse_vec3(t_vec3 *out)
{
	float vals[3];
	const char *str;
	char *end;
	for (int i = 0; i < 3; ++i)
	{
		str = ft_strtok(NULL, " \t\n,");
		if (!str)
			return (1);
		vals[i] = ft_strtof(str, &end);
		if (end == str || *end != '\0')
			return (1);
	}
	out->x = vals[0];
	out->y = vals[1];
	out->z = vals[2];
	return (0);
}

int parse_camera(void)
{
	char *fov_str;
	float fov;
	char *end;

	if (parse_vec3(&g_camera.position))
		return 1;
	if (parse_vec3(&g_camera.orientation))
		return 1;
	float len = vec3_length(g_camera.orientation);
	if (len < 1.0f - EPSILON || len > 1.0f + EPSILON)
		return 1;
	fov_str = ft_strtok(NULL, " \t\n");
	if (!fov_str)
		return 1;
	fov = ft_strtof(fov_str, &end);
	if (end == fov_str || *end != '\0' || fov < 0.0f || fov > 180.0f)
		return 1;
	g_camera.fov = fov;
	return 0;
}

int parse_ambient(void) {
	if (parse_intensity(&g_ambient_light.intensity))
		return 1;
	if (parse_rgb(&g_ambient_light.color))
		return 1;
	return 0;
}

// Main parse function
int	parse(int fd)
{
	char *line;
	char *id;

	line = get_next_line(fd);
	while (line)
	{
		id = ft_strtok(line, " \t\n");
		if (id)
		{
			if (dispatch_parse(id, fd))
			{
				write(2, "Error\n", 6);
				free(line);
				return (1);
			}
			free(line);
			break;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

