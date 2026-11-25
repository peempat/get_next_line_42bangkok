/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peem <peem@student.42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 00:00:00 by peem              #+#    #+#             */
/*   Updated: 2026/11/23 00:00:00 by peem             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_batch(int fd, char *batch, size_t target, size_t size)
{
	size_t	used;
	ssize_t	count;

	used = 0;
	batch[0] = '\0';
	while (used < target)
	{
		count = read(fd, batch + used, size);
		if (count <= 0)
			return ((int)count);
		batch[used + count] = '\0';
		if (ft_strchr(batch + used, '\n'))
			return (0);
		used += count;
	}
	return (1);
}

static char	*join_batch(char *stash, char *batch, int status)
{
	char	*joined;

	joined = NULL;
	if (status >= 0 && stash)
		joined = ft_strjoin(stash, batch);
	else if (status >= 0 && batch[0])
		joined = ft_strdup(batch);
	free(stash);
	free(batch);
	return (joined);
}

static char	*read_stash(int fd, char *stash, size_t size)
{
	size_t	target;
	char	*batch;
	int		status;

	target = size;
	while (1)
	{
		batch = malloc(target + size);
		if (!batch)
			break ;
		status = read_batch(fd, batch, target, size);
		stash = join_batch(stash, batch, status);
		if (!stash || status <= 0)
			return (stash);
		target = ft_strlen(stash);
	}
	free(stash);
	return (NULL);
}

static char	*split_line(char **stash)
{
	char	*line;
	char	*newline;

	line = *stash;
	*stash = NULL;
	newline = ft_strchr(line, '\n');
	if (newline && newline[1])
	{
		*stash = ft_strdup(newline + 1);
		if (!*stash)
		{
			free(line);
			return (NULL);
		}
		newline[1] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		probe;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &probe, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (!stash || !ft_strchr(stash, '\n'))
		stash = read_stash(fd, stash, BUFFER_SIZE);
	if (!stash)
		return (NULL);
	return (split_line(&stash));
}
