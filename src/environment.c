/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:28:22 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/10 20:17:31 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_gvar	*g(void)
{
	static t_gvar	data = {
		.light_capacity = 4,
		.object_capacity = 4,
	};

	return (&data);
}
