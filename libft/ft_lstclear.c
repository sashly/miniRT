/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:45:09 by sashly            #+#    #+#             */
/*   Updated: 2020/11/06 12:11:58 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *todel;

	if (!*lst || !lst || !del)
		return ;
	while (*lst)
	{
		todel = *lst;
		*lst = (*lst)->next;
		(*del)(todel->content);
		free(todel);
	}
}
