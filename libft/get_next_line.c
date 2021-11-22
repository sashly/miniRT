/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:59:24 by sashly            #+#    #+#             */
/*   Updated: 2021/03/01 19:59:32 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t origlen, size_t newlen)
{
	void *realloc;

	if (newlen == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (newlen <= origlen)
		return (ptr);
	if (!(realloc = malloc(newlen)))
	{
		free(ptr);
		return (NULL);
	}
	ft_memset(realloc, 0, newlen);
	realloc = (ptr) ? ft_memcpy(realloc, ptr, origlen) : realloc;
	free(ptr);
	return (realloc);
}

int		error_handle(char **line)
{
	if (*line)
		free(*line);
	return (-1);
}

int		ft_strlen_mod(const char *str, int start, int *index)
{
	int i;

	i = start;
	while (str[i] && str[i] != '\n')
		i++;
	*index = (str[i]) ? (i + 1) : 0;
	return (i - start);
}

int		get_next_line(int fd, char **line)
{
	int				ret;
	int				olen;
	int				nlen;
	static t_buf	mbuf;

	if (BUFFER_SIZE <= 0 || fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	nlen = 0;
	mbuf.offset = mbuf.index;
	while (1)
	{
		ret = (!mbuf.index) ? (read(fd, mbuf.buf, BUFFER_SIZE)) : 1;
		if (ret == -1)
			return (error_handle(line));
		olen = nlen;
		nlen = olen + ft_strlen_mod(mbuf.buf, mbuf.offset, &mbuf.index);
		DEF_PTR(*line = (char *)ft_realloc(*line, olen, nlen + 1));
		ft_strlcat(*line, mbuf.buf + mbuf.offset, nlen + 1);
		if (mbuf.index || !ret)
			break ;
		mbuf.offset = 0;
		ft_memset(mbuf.buf, 0, BUFFER_SIZE);
	}
	return ((ret) ? 1 : 0);
}
