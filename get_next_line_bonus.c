/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:32:31 by tbertoli          #+#    #+#             */
/*   Updated: 2021/03/03 20:38:09 by tbertoli         ###   ########.fr       */
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

void	ft_swoppa(char **riga_add, char *buffer_add)
{
	char *temp;

	temp = ft_strjoin(*riga_add, buffer_add);
	ft_libera(riga_add);
	*riga_add = ft_strdup(temp);
	ft_memset(buffer_add, 0, ft_strlen(buffer_add));
	ft_libera(&temp);
}

int		get_next_line(int fd, char **line)
{
	static char	bf[1000][BUFFER_SIZE + 1];
	char		temp[BUFFER_SIZE];
	char		*p;
	int			n;

	bf[fd][BUFFER_SIZE] = 0;
	p = NULL;
	n = 0;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	ft_libera(line);
	while (!(p = ft_strchr(bf[fd], '\n')))
	{
		ft_swoppa(line, bf[fd]);
		if (((n = read(fd, bf[fd], BUFFER_SIZE))) == 0 && (ft_strlen(bf[fd]) == 0))
			return (0);
		else if (!(p = ft_strchr(bf[fd], '\n')))
		{
			ft_swoppa(line, bf[fd]);
		}
		else if (n < BUFFER_SIZE && !p)
		{
			ft_swoppa(line, bf[fd]);
			break ;
		}
		else if (p)
		{
			*p = '\0';
			ft_swoppa(line, bf[fd]);
			ft_strlcpy(temp, p + 1, ft_strlen(p + 1) + 1);
			ft_memset(bf[fd], 0, BUFFER_SIZE);
			ft_strlcpy(bf[fd], temp, BUFFER_SIZE);
			break ;
		}
		else
			return (-1);
		ft_memset(bf[fd], 0, BUFFER_SIZE);
	}
	return (1);
}