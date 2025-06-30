/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:59:46 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/30 16:55:59 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int	process_object_arr_size(void)
{
	t_object	*new_objects;

	if (!g()->objects)
	{
		g()->objects = malloc(sizeof(t_object) * g()->object_capacity);
		if (!g()->objects)
			return (1);
	}
	if (g()->object_count >= g()->object_capacity)
	{
		new_objects = ft_realloc(g()->objects,
				sizeof(t_object) * g()->object_capacity,
				sizeof(t_object) * g()->object_capacity << 1);
		if (!new_objects)
		{
			free(g()->objects);
			g()->objects = NULL;
			return (1);
		}
		g()->objects = new_objects;
		g()->object_capacity <<= 1;
	}
	return (0);
}
