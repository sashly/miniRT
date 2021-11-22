/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:07:40 by sashly            #+#    #+#             */
/*   Updated: 2020/11/06 13:01:20 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;

	if (c == '\0' && *s)
		return (1);
	else if (c == '\0' && !*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
			if (*(++s) == c || !*s)
				count++;
	}
	return (count);
}

static int	ft_strlen_mod(char const *s, char c)
{
	char const	*ps;

	ps = s;
	while (*ps && *ps != c)
		ps++;
	return (ps - s);
}

static char	*ft_strdup_mod(const char *s, int len)
{
	char *dup;
	char *d;

	if (!(dup = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	d = dup;
	while (*s && len--)
		*(dup++) = *(s++);
	*dup = '\0';
	return (d);
}

static void	clean_leaks(char **split, int n)
{
	int i;

	i = 0;
	while (i < n)
		free(split[i++]);
	free(split);
}

char		**ft_split(char const *s, char c)
{
	char	**split;
	int		size;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	size = count_words(s, c);
	if (!(split = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		while (*s && *s == c)
			s++;
		len = ft_strlen_mod(s, c);
		if (!(split[i++] = ft_strdup_mod(s, len)))
		{
			clean_leaks(split, --i);
			return (NULL);
		}
		s = s + len;
	}
	split[i] = NULL;
	return (split);
}
