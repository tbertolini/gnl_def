/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:53:35 by tbertoli          #+#    #+#             */
/*   Updated: 2021/02/23 19:54:37 by tbertoli         ###   ########.fr       */
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
	//printf("è qui che crashi?");
	temp = ft_strjoin(*riga_add, buffer_add);
	//printf("riga contiene:\t%s\nbuffer contiene:\t%s\ntemp:\t%s\n",*riga_add,buffer_add, temp);
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
	static char linea_successiva[BUFFER_SIZE + 1];

	riga = NULL;
	letti = BUFFER_SIZE ;
	eof = 0;
	if (fd <= 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (linea_successiva[0] != '\0')
	{
		letti = ft_strlcpy(buffer, linea_successiva, ft_strlen(linea_successiva) + 1);
		ft_memset(linea_successiva, 0, ft_strlen(linea_successiva));
	}
	while ((punt = ft_strchr(buffer, '\n')) == NULL && eof == 0)
	{
		buffer[letti] = 0;
		ft_swoppa(&riga ,buffer);
		if ((letti = read(fd, buffer, BUFFER_SIZE))  == 0)
			eof = 1;
	}
	if (eof == 1 && !(punt = ft_strchr(buffer, '\n')))  //cosa succede se c'è eof ma c'è anche endline??
	{
		buffer[letti] = 0;
		ft_swoppa(&riga, buffer);
		*line = ft_strdup(riga);
		ft_libera(&riga);
		return 0;
	}
	else //((punt = ft_strchr(buffer, '\n')))
	{
		buffer[letti] = 0;
		ft_strlcpy(linea_successiva, punt + 1, ft_strlen(punt) + 1);
		*punt = 0;
		ft_swoppa(&riga, buffer);
	}
	//else
	//	return (-1);
	*line = ft_strdup(riga);
	ft_libera(&riga);
	return (1);			
}
