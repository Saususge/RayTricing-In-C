/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/30 17:06:20 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include "sphere.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int	parse_sphere(void)
{
	t_point		center;
	float		diameter;
	t_vec3		color;
	char		*center_str;
	char		*diameter_str;
	char		*color_str;

	center_str = ft_strtok(NULL, " \t\n");
	diameter_str = ft_strtok(NULL, " \t\n");
	color_str = ft_strtok(NULL, " \t\n");
	if (parse_vec3(center_str, (t_vec3 *)&center)
		|| parse_float(diameter_str, &diameter)|| diameter <= 0.0f
		|| parse_vec3(color_str, &color)
		|| process_object_arr_size())
		return (1);
	g()->objects[g()->object_count++] = create_sphere(
											center,
											diameter * 0.5f, color);
	return (0);
}
