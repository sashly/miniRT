/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:48:55 by sashly            #+#    #+#             */
/*   Updated: 2020/11/06 12:46:42 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *newlst;
	t_list *newlst_n;

	if (!lst)
		return (NULL);
	newlst = NULL;
	while (lst)
	{
		if (!(newlst_n = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newlst_n);
		lst = lst->next;
	}
	return (newlst);
}
