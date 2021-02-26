/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:53:35 by tbertoli          #+#    #+#             */
/*   Updated: 2021/02/26 20:37:29 by tbertoli         ###   ########.fr       */
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
	size_t letti;
	int eof;
	char buffer[BUFFER_SIZE + 1];
	char *punt;
	char *riga;
	static char successiva[BUFFER_SIZE + 1];

	buffer[BUFFER_SIZE] = 0;
	riga = NULL;
	letti = BUFFER_SIZE;
	eof = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (successiva[0] != '\0')
		letti = ft_strlcpy(buffer, successiva, ft_strlen(successiva) + 1);
	ft_memset(successiva, 0, ft_strlen(successiva));
	while ((punt = ft_strchr(buffer, '\n')) == NULL)
	{
		ft_swoppa(&riga, buffer);
		if ((letti = read(fd, buffer, BUFFER_SIZE)) == 0)
			break ;
	}
	if (!punt)
	{
		ft_swoppa(&riga, buffer);
		eof = 0;
	}
	else
	{
		ft_strlcpy(successiva, punt + 1, ft_strlen(punt) + 1);
		*punt = 0;
		ft_swoppa(&riga, buffer);
	}
	*line = ft_strdup(riga);
	ft_libera(&riga);
	return (eof);
}
