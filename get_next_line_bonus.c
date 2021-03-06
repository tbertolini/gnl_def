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

#include "get_next_line_bonus.h"

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

int	ft_swoppa(char **dest, char *source, int c)
{
	char	*temp;

	source[c] = 0;
	temp = ft_strjoin(*dest, source);
	ft_libera(dest);
	*dest = ft_strdup(temp);
	ft_libera(&temp);
	if (ft_strchr(*dest, '\n'))
		return (1);
	return (0);
	
}

int		get_next_line(int fd, char **line)
{
	static char *eccedenza[MAX_INPUT];
	char		*temp;
	char		*p;
	int			c;
	char		bf[BUFFER_SIZE + (c = 1)];

	temp = NULL;
	if (fd < 0 || fd >= 1000 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (eccedenza[fd] == NULL)
		eccedenza[fd] = ft_strdup("");
	while((c = read(fd, bf, BUFFER_SIZE)) > 0)
		if (ft_swoppa(&eccedenza[fd], bf, c) == 1)
			break ;
	if ((p = ft_strchr(eccedenza[fd], '\n')))
	{
		*p = 0;
		temp = ft_strdup(p + 1);
	}
	*line = ft_strdup(eccedenza[fd]);
	ft_libera(&eccedenza[fd]);
	eccedenza[fd] = (temp != NULL) ? ft_strdup(temp) : NULL;
	ft_libera(&temp);
	return (c > 0 || eccedenza[fd] != NULL);
}