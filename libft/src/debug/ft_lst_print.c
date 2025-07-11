/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:16:26 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/06 20:01:59 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef DEBUG

void	ft_lst_print(t_list *lst, void (*print_content)(void *))
{
	while (lst)
	{
		print_content(lst->content);
		lst = lst->next;
	}
}
#endif