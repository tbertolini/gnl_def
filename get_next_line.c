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

void	ft_libera(char **s1)
{
	if (*s1)
	{
		ft_memset(*s1, 0, ft_strlen(*s1));
		free(*s1);
		*s1 = NULL;
	}
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	int			ck;
	char		*temp;
	char		*riga;
	char		buffer[BUFFER_SIZE];
	static char	prox_linea[BUFFER_SIZE];

	ret = 1;
	ck = 0;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while (!ft_strchr(buffer, '\n') && (ck = read(fd, buffer, BUFFER_SIZE)) > 1)
	{
		buffer[ck] = 0;
		temp = ft_strjoin(riga, buffer);
		ft_libera(&riga);
		riga = ft_strdup(temp);
		ft_memset(buffer, 0, ft_strlen(buffer));
		ft_libera(&temp);
	}
	if (ck == 0)
		ret = 0;
	else if (ck > 0)
	{
		//aggiungi il resto della linea a riga e metti il resto in prox_linea, in modo puilito!!
		// 
	}
	*line = ft_strdup(riga);
	ft_libera(&riga);
	return (ret);
}
