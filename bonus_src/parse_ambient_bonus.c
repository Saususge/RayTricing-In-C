/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/11 13:19:50 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static int	parse_ambient_intensity(t_vec3 *intensity)
{
	char	*intensity_str;
	char	*rgb_str;
	float	temp_float;
	t_vec3	temp_color;

	intensity_str = ft_strtok(NULL, " \t\n");
	rgb_str = ft_strtok(NULL, " \t\n");
	if (parse_float(intensity_str, &temp_float)
		|| temp_float < 0.0f || temp_float > 1.0f)
		return (1);
	if (parse_vec3(rgb_str, &temp_color))
		return (1);
	intensity->x = temp_color.x / 255.0f * temp_float;
	intensity->y = temp_color.y / 255.0f * temp_float;
	intensity->z = temp_color.z / 255.0f * temp_float;
	return (0);
}

int	parse_ambient(void)
{
	t_ambient_light	amb;
	static int		init;

	if (init)
	{
		ft_putstr_fd("Ambient light already defined\n", STDERR_FILENO);
		return (1);
	}
	if (parse_ambient_intensity(&amb.intensity))
		return (1);
	g()->amb_light = amb;
	init = 1;
	return (0);
}
