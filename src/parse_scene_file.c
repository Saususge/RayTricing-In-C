/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:11:57 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 18:12:35 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "object.h"
#include "libft.h"
#include <stdlib.h>
#include "parse.h"

void	parse_scene_file(const char *filename)
{
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Could not open scene file.\n", STDERR_FILENO);
		exit(1);
	}
	if (parse(fd))
	{
		ft_putstr_fd("Error: Failed to parse scene file.\n", STDERR_FILENO);
		free(g()->lights);
		free(g()->objects);
		exit(1);
	}
	close(fd);
}
