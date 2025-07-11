/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:08:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/26 21:17:57 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Helper to parse mantissa part after '.'
static float	parse_mantissa(const char **str_ptr)
{
	float		result;
	float		factor;
	const char	*str;

	result = 0.0f;
	factor = 0.1f;
	str = *str_ptr;
	while (*str >= '0' && *str <= '9')
	{
		result += (*str++ - '0') * factor;
		factor *= 0.1f;
	}
	*str_ptr = str;
	return (result);
}

float	ft_strtof(const char *str, char **endptr)
{
	float	result;
	float	sign;

	result = 0.0f;
	sign = 1.0f;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1.0f;
		++str;
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10.0f + (*str++ - '0');
	if (*str == '.')
	{
		++str;
		result += parse_mantissa(&str);
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}
