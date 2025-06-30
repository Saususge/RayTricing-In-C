/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:34:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/30 16:58:01 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include "parse.h"
#include "plane.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int	parse_plane(void)
{
	t_point		center;
	t_vec3		normal;
	t_vec3		color;
	char		*center_str;
	char		*normal_str;
	char		*color_str;
	float		mag;

	center_str = ft_strtok(NULL, " \t\n");
	normal_str = ft_strtok(NULL, " \t\n");
	color_str = ft_strtok(NULL, " \t\n");
	if (parse_vec3(center_str, (t_vec3 *)&center))
		return (1);
	if (parse_vec3(normal_str, &normal))
		return (1);
	mag = vec3_length(normal);
	if (mag < 1.0f - EPSILON || mag > 1.0f + EPSILON)
		return (1);
	if (parse_vec3(color_str, &color))
		return (1);
	if (process_object_arr_size())
		return (1);
	g()->objects[g()->object_count++] = create_plane(center, normal, color);
	return (0);
}
