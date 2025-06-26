/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:59:46 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/26 23:52:35 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

t_object		**g_objects;
int				g_object_count;
int				g_object_capacity = 4;

int process_object_arr_size(void)
{
	t_object	**new_objects;

	if (!g_objects)
	{
		g_objects = malloc(sizeof(t_object *) * g_object_capacity);
		if (!g_objects)
			return (1);
	}
	if (g_light_count >= g_object_capacity)
	{
		new_objects = ft_realloc(g_objects,
						sizeof(t_object *) * g_object_capacity,
						sizeof(t_object *) * g_object_capacity << 1);
		if (!new_objects)
		{
			free(g_objects);
			g_objects = NULL;
			return (1);
		}
		g_objects = new_objects;
		g_object_capacity <<= 1;
	}
	return (0);
}
