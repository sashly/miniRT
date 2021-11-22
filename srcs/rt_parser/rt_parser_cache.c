/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_cache.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:21:30 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:21:53 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int	cache_file(int fd, t_list **head)
{
	char	*line;
	int		gnl;
	char	**split;

	gnl = 1;
	while (gnl)
	{
		if ((gnl = get_next_line(fd, &line)) == -1)
		{
			if (*head)
				ft_lstclear(head, &del_split);
			return (0);
		}
		if (*line && *line != '#')
		{
			if (!(split = ft_split(line, ' ')))
				return (free_ptrs_ret(line, NULL, NULL, 0));
			ft_lstadd_front(head, ft_lstnew((void *)split));
		}
		free(line);
	}
	return (!close(fd));
}

int	cc_cache_helper(char **errstr, char *str, int ret)
{
	*errstr = str;
	return (ret);
}

int	check_and_count_cache(t_list *head, int *count, char **errstr)
{
	char	**split;
	int		cid;
	int		index;

	ft_memset((void *)count, 0, sizeof(int) * IND_COUNT_SIZE);
	while (head)
	{
		split = (char **)head->content;
		if ((cid = count_ident(split[0], count, &index)) != 1)
			return (cc_cache_helper(errstr, split[0], cid));
		if (!(check_ident_spec(split, index)))
			return (cc_cache_helper(errstr, split[0], ERR_INVSPEC));
		head = head->next;
	}
	if (!count[0] || !count[3])
		return (cc_cache_helper(errstr, (!count[3]) ? "R" : "c", ERR_MISSRTY));
	return (1);
}
