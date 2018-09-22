/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 22:41:11 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/21 20:26:40 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <unistd.h>

static t_buff	*buff_new(void)
{
	t_buff	*b;

	if ((b = (t_buff*)malloc(sizeof(t_buff))) == NULL)
		return (NULL);
	b->cur = NULL;
	if ((b->start = (char*)malloc(BUFF_SIZE + 1)) == NULL)
		return (NULL);
	b->cur = b->start;
	ft_bzero(b->start, BUFF_SIZE + 1);
	return (b);
}

static int		copy_line(t_buff *data, char *end, char **dst)
{
	char	*del;

	*end = '\0';
	del = *dst;
	ALLOC_CHECK(*dst = ft_strjoin(*dst, data->cur));
	free(del);
	data->cur = end + 1;
	return (1);
}

static int		end(t_buff *data, char **line)
{
	int	status;

	status = copy_line(data, data->start + BUFF_SIZE, line);
	data->cur = NULL;
	return (status);
}

static int		fill_buff(int fd, t_buff *data, char **line)
{
	char	*nl;
	char	*del;
	size_t	nread;

	nread = 0;
	while ((nl = ft_strchr(data->cur, '\n')) == NULL)
	{
		if (nread > 0 && nread != BUFF_SIZE)
			return (end(data, line));
		if (data->cur != data->start || nread == BUFF_SIZE)
		{
			del = *line;
			*line = ft_strjoin(*line, data->cur);
			free(del);
			ft_bzero(data->start, BUFF_SIZE);
		}
		nread = read(fd, data->start, BUFF_SIZE);
		if (nread == 0 && **line != '\0')
			return (end(data, line));
		data->cur = data->start;
		if (nread < 1)
			return (nread);
	}
	return (copy_line(data, nl, line));
}

int				get_next_line(int fd, char **line)
{
	static t_buff	*data[256] = {NULL};

	if (fd < 0 || line == NULL)
		return (-1);
	if (data[fd] == NULL)
	{
		ALLOC_CHECK(data[fd] = buff_new());
	}
	else if (data[fd]->cur == NULL)
	{
		free(data[fd]->start);
		free(data[fd]);
		return (0);
	}
	ALLOC_CHECK(*line = ft_strdup(""));
	return (fill_buff(fd, data[fd], line));
}
