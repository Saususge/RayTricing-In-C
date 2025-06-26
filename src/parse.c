/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/26 23:54:00 by wchoe            ###   ########.fr       */
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
	if (!ft_memcmp(id, "A", 2))
		return (parse_ambient());
	if (!ft_memcmp(id, "C", 2))
		return (parse_camera());
	if (!ft_memcmp(id, "L", 2))
		return (parse_light());
	if (!ft_memcmp(id, "sp", 3))
		return (parse_sphere());
	if (!ft_memcmp(id, "pl", 3))
		return (parse_plane());
	// if (!ft_memcmp(id, "cy", 3))
	// 	return (parse_cylinder());
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
			free(line);
			break;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

