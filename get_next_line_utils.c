/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:02:51 by tbertoli          #+#    #+#             */
/*   Updated: 2021/02/23 19:54:40 by tbertoli         ###   ########.fr       */
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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t n;

	if (!(src))
		return (0);
	if (!(dest) || size == 0)
		return (ft_strlen(src));
	n = 0;
	while (src[n] && n < (size - 1))
	{
		dest[n] = (char)src[n];
		n++;
	}
	dest[n] = 0;
	while (src[n])
	{
		n++;
	}
	return (n);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (((char*)str) + i);
		i++;
	}
	if (str[i] == c)
		return (((char*)str) + i);
	return (NULL);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	n_len;
	size_t	i;
	char	*j;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	n_len = ft_strlen(s1) + ft_strlen(s2);
	if (!(j = (char*)malloc((n_len + 1) * sizeof(char))))
		return (NULL);
	i = ft_strlcpy(j, s1, (ft_strlen(s1) + 1));
	ft_strlcat((j + ft_strlen(s1)), s2, (ft_strlen(s2) + 1));
	return (j);
}

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_length;
	size_t	src_length;

	src_length = ft_strlen(src);
	dest_length = ft_strlen(dst);
	j = dest_length;
	i = 0;
	if (dest_length < size - 1 && size > 0)
	{
		while (src[i] && dest_length + i < size - 1)
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = 0;
	}
	if (dest_length >= size)
		dest_length = size;
	return (dest_length + src_length);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t n;

	if (!b)
		return (NULL);
	n = 0;
	while (n < len)
	{
		*(unsigned char*)((b + n)) = (char)c;
		n++;
	}
	return (b);
}
