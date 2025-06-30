/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:28:22 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/30 16:53:59 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_gvar	*g(void)
{
	static t_gvar	data = {
		.light_capacity = 4,
		.object_capacity = 4,
		.k_a = 0.2,
		.k_d = 10,
		.k_s = 10,
	};
	
	return (&data);
}