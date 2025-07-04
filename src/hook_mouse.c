/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:46:34 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 18:35:37 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "event.h"
#include "transform.h"
#include "libft.h"
#include "hit.h"
#include "mlx.h"
#include <unistd.h>

int	mouse_hook(int button, int x, int y, void *mlx)
{
	char	*object;
	t_hit	hit;

	(void)mlx;
	if (button == 1)
	{
		if (shoot_ray_from_viewport(x, y, &hit))
		{
			g()->camera_choosed = 0;
			g()->light_choosed = 0;
			g()->choosen_object = hit.object;
			if (g()->choosen_object->type == SPHERE)
				object = "Sphere";
			else if (g()->choosen_object->type == PLANE)
				object = "Plane";
			else if (g()->choosen_object->type == CYLINDER)
				object = "Cylinder";
			else
				object = "Cone";
			ft_printf("Object %u(%s) selected\n",
				g()->choosen_object - g()->objects + 1, object);
		}
	}
	return (0);
}
