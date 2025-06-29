/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/30 04:06:06 by chakim           ###   ########.fr       */
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
	if (!ft_strcmp(id, "pl"))
		return (parse_plane());
	if (!ft_strcmp(id, "cy"))
		return (parse_cylinder());
	return (1);
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

