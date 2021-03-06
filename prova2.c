/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:53:35 by tbertoli          #+#    #+#             */
/*   Updated: 2021/03/04 13:14:03 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1) + 1;
	s2 = (char *)malloc(sizeof(char) * len);
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, len);
	return (s2);
}

size_t	ft_strlen(const char *str)
{
	size_t	n;
	char	*pchar;

	n = 0;
	pchar = (char *)str;
	while (*pchar != 0)
	{
		n++;
		pchar++;
	}
	return (n);
}

int		ft_libera(char **s1)
{
	if (*s1)
	{
		ft_memset(*s1, 0, ft_strlen(*s1));
		free(*s1);
		*s1 = NULL;
		return (1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char *eccedenza;
	char		*temp;
	char		*p;
	char		bf[BUFFER_SIZE + 1];
	int			c;

	temp = NULL;
	c = 1;
	if (fd < 0 || fd >= 1000 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while((c = read(fd, bf, BUFFER_SIZE)) > 0)
	{
		bf[c] = 0;
		temp = ft_strjoin(eccedenza, bf);
		ft_libera(&eccedenza);
		eccedenza = ft_strdup(temp);
		ft_libera(&temp);
		if ((p = ft_strchr(eccedenza, '\n')))
			break ;
	}
	if (c > 0)
	{
		*line = ft_substr(eccedenza, 0, (p - eccedenza));
		temp = ft_strdup(p + 1);
		ft_libera(&eccedenza);
		eccedenza = ft_strdup(temp);
		ft_libera(&temp);
	}
	else if (c == 0)
	{
		*line = ft_strdup(eccedenza);
		ft_libera(&eccedenza);
		eccedenza = NULL;
	}
	return (c > 0 || eccedenza != NULL);
}
