/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:57:16 by wchoe             #+#    #+#             */
/*   Updated: 2025/06/26 15:20:05 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*internal_str;
	char		*token;

	if (str != NULL)
		internal_str = str;
	if (internal_str == NULL)
		return (NULL);
	while (*internal_str && ft_strchr(delim, *internal_str))
		++internal_str;
	if (*internal_str == '\0')
	{
		internal_str = NULL;
		return (NULL);
	}
	token = internal_str;
	while (*internal_str && !ft_strchr(delim, *internal_str))
		++internal_str;
	if (*internal_str != '\0')
		*internal_str++ = '\0';
	return (token);
}
