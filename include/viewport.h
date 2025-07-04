/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:36:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/04 16:36:26 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWPORT_H
# define VIEWPORT_H
# include "object.h"

typedef struct s_viewport
{
	int		width;
	int		height;
	float	aspect_ratio;
	float	focal_length;
	float	view_w;
	float	view_h;
	t_vec3	vup;
	t_vec3	view_u;
	t_vec3	view_v;
	t_vec3	view_u_per_pixel;
	t_vec3	view_v_per_pixel;
	t_vec3	view_upper_left;
	t_vec3	pixel_origin;
}	t_viewport;

void	set_viewport(void);
#endif
