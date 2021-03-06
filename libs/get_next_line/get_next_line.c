/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 00:54:21 by auhoris           #+#    #+#             */
/*   Updated: 2020/12/06 00:54:32 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	treat_reminder(char **reminder, char **line, char **nl_ptr)
{
	char	*tmp;

	*nl_ptr = ft_nlpos(*reminder);
	if (*nl_ptr != NULL)
	{
		**nl_ptr = '\0';
		if ((*line = ft_strdup(*reminder)) == NULL ||
				(tmp = ft_strdup(++(*nl_ptr))) == NULL)
			return (-1);
		free(*reminder);
		*reminder = tmp;
	}
	else if (*reminder != NULL)
	{
		*line = *reminder;
		*reminder = NULL;
	}
	else
	{
		if ((*line = ft_strdup("")) == NULL)
			return (-1);
	}
	return (0);
}

static int	ft_checkbuf(char **reminder, char *nl_ptr)
{
	char	*tmp;

	*nl_ptr = '\0';
	tmp = *reminder;
	if ((*reminder = ft_strdup(++nl_ptr)) == NULL)
		return (-1);
	if (tmp != NULL)
		free(tmp);
	return (0);
}

int			check_fd(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	bytes_read = read(fd, buffer, 0);
	if (bytes_read < 0)
		return (0);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*nl_ptr;
	int			bytes_read;
	char		*leakline;
	static char	*reminder;

	bytes_read = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || line == NULL || !check_fd(fd))
		return (-1);
	if (treat_reminder(&reminder, line, &nl_ptr) == -1)
		return (-1);
	while (!nl_ptr && (bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytes_read] = '\0';
		if ((nl_ptr = ft_nlpos(buffer)) != NULL)
			if (ft_checkbuf(&reminder, nl_ptr) == -1)
				return (-1);
		leakline = *line;
		if ((*line = ft_strjoin(*line, buffer)) == NULL)
			return (-1);
		free(leakline);
	}
	return ((nl_ptr) ? 1 : 0);
}
