/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/26 23:10:26 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int	parse_sphere(void)
{
	t_point		center;
	float		diameter;
	t_color		color;
	char		*center_str;
	char		*diameter_str;
	char		*color_str;

	center_str = ft_strtok(NULL, " \t\n");
	diameter_str = ft_strtok(NULL, " \t\n");
	color_str = ft_strtok(NULL, " \t\n");
	if (parse_vec3(center_str, (t_vec3 *)&center))
		return (1);
	if (parse_float(diameter_str, &diameter) || diameter <= 0.0f)
		return (1);
	if (parse_color(color_str, &color))
		return (1);
	// TODO: Add sphere object to the scene, g_objects array
	return (0);
}
