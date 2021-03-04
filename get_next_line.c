/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:53:35 by tbertoli          #+#    #+#             */
/*   Updated: 2021/03/04 09:48:42 by tbertoli         ###   ########.fr       */
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

void	ft_libera(char **s1)
{
	if (*s1)
	{
		ft_memset(*s1, 0, ft_strlen(*s1));
		free(*s1);
		*s1 = NULL;
	}
}

int		ft_swoppa(char **riga_add, char *buffer_add)
{
	char *p;
	char *temp;

	if ((p = ft_strchr(buffer_add, '\n')))
		*p = 0;
	temp = ft_strjoin(*riga_add, buffer_add);
	ft_libera(riga_add);
	*riga_add = ft_strdup(temp);
	if (p == NULL)
	{
		ft_memset(buffer_add, 0, ft_strlen(buffer_add));
		ft_libera(&temp);
		return (0);
	}
	ft_libera(&temp);
	temp = ft_strdup(p + 1);
	ft_memset(buffer_add, 0, BUFFER_SIZE);
	ft_strlcpy(buffer_add, temp, ft_strlen(temp) + 1);
	ft_libera(&temp);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	bf[BUFFER_SIZE + 1];
	int			n;
	int			b_letti;

	bf[BUFFER_SIZE] = 0;
	n = 0;
	if (fd < 0 || fd >= 1000 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (bf[0] == '\n')
	{
		ft_strlcpy(bf, bf + 1, BUFFER_SIZE);
		*line = ft_strdup("");
		return (1);
	}
	ft_libera(line);
	n = ft_swoppa(line, bf);
	while ((b_letti = read(fd, bf, BUFFER_SIZE)) > 0)
	{
		if ((n = ft_swoppa(line, bf)) != 0)
			break ;
	}
	return (n || (b_letti == BUFFER_SIZE));
}
