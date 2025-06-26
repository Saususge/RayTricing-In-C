/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:59:46 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/26 23:03:46 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int process_object_arr_size(void)
{
	t_object	*new_objects;

	if (!g_lights)
	{
		g_lights = malloc(sizeof(t_object) * g_object_capacity);
		if (!g_lights)
			return (1);
	}
	if (g_light_count >= g_object_capacity)
	{
		new_objects = ft_realloc(g_lights,
						sizeof(t_object) * g_object_capacity,
						sizeof(t_object) * g_object_capacity << 1);
		if (!new_objects)
		{
			free(g_lights);
			g_objects = NULL;
			return (1);
		}
		g_lights = new_objects;
		g_object_capacity <<= 1;
	}
	return (0);
}
