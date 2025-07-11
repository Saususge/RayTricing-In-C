/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:46:34 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/11 13:47:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "event.h"
#include "transform.h"
#include "libft.h"
#include "hit.h"
#include "mlx.h"
#include <unistd.h>
#include <stdio.h>

int	mouse_hook(int button, int x, int y, void *mlx)
{
	char		*object;
	t_object	*obj;
	t_vec3		color;

	(void)mlx;
	if (button == 1)
	{
		if (shoot_ray_from_viewport(x, y, &obj, &color))
		{
			g()->camera_choosed = 0;
			g()->light_choosed = 0;
			g()->choosen_object = obj;
			if (g()->choosen_object->type == SPHERE)
				object = "Sphere";
			else if (g()->choosen_object->type == PLANE)
				object = "Plane";
			else if (g()->choosen_object->type == CYLINDER)
				object = "Cylinder";
			else
				object = "Cone";
			printf("Object %lu(%s) selected\n",
				g()->choosen_object - g()->objects + 1, object);
		}
	}
	return (0);
}
