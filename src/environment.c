/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:28:22 by wchoe             #+#    #+#             */
/*   Updated: 2025/07/11 13:41:43 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_gvar	*g(void)
{
	static t_gvar	data = {
		.object_capacity = 4,
		.light_capacity = 1,
	};

	return (&data);
}
