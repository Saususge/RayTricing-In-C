/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/26 22:52:58 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int	parse_ambient(void)
{
	t_ambient_light amb;
	char *intensity_str;
	char *rgb_str;

	intensity_str = ft_strtok(NULL, " \t\n");
	rgb_str = ft_strtok(NULL, " \t\n");
	if (parse_float(intensity_str, &amb.intensity)
		|| amb.intensity < 0.0f || amb.intensity > 1.0f)
		return (1);
	if (parse_color(rgb_str, &amb.color))
		return (1);
	g_ambient_light = amb;
	return (0);
}
