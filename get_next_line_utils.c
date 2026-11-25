/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peem <peem@student.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 00:00:00 by peem              #+#    #+#             */
/*   Updated: 2026/11/23 00:00:00 by peem             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(s) + 1;
	copy = malloc(len);
	if (copy)
		ft_memcpy(copy, s, len);
	return (copy);
}

char	*ft_strjoin(const char *left, const char *right)
{
	size_t	left_len;
	size_t	right_len;
	char	*joined;

	left_len = ft_strlen(left);
	right_len = ft_strlen(right);
	joined = malloc(left_len + right_len + 1);
	if (!joined)
		return (NULL);
	ft_memcpy(joined, left, left_len);
	ft_memcpy(joined + left_len, right, right_len + 1);
	return (joined);
}
