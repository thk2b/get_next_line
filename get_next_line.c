/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 22:41:11 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/21 19:18:40 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <unistd.h>

static t_buff	*buff_new(void)
{
	t_buff	*b;

	if((b = (t_buff*)malloc(sizeof(t_buff))) == NULL)
		return (NULL);
	b->cur = NULL;
	if((b->start = (char*)malloc(BUFF_SIZE + 1)) == NULL)
		return (NULL);
	b->cur = b->start;
	ft_bzero(b->start, BUFF_SIZE + 1);
	return (b);
}

static	int	copy_line(t_buff *data, char *end, char **dst)
{
	char	*del;

	*end = '\0';
	del = *dst;
	ALLOC_CHECK(*dst = ft_strjoin(*dst, data->cur));
	free(del);
	data->cur = end + 1;
	return (1);
}

// static int	fill_buff(t_buff *data, char **dst)
// {

// }

int		get_next_line(int fd, char **line)
{
	static t_buff	*data[256] = {NULL};
	char			*nl;
	ssize_t			nread;
	int				status;
	char			*del;

	if (fd < 0 || line == NULL)
		return (-1);
	if (data[fd] == NULL) // no t_buff
	{
		ALLOC_CHECK(data[fd] = buff_new());
	}
	else if (data[fd]->cur == NULL) // reached OEF
	{
		free(data[fd]->start);
		free(data[fd]);
		return (0);
	}
	ALLOC_CHECK(*line = ft_strdup(""));
	nread = 0;
	while ((nl = ft_strchr(data[fd]->cur, '\n')) == NULL)
	{
		if (nread > 0 && nread != BUFF_SIZE) // didn't find a newline but cound not read whole buffer: reached EOF
		{
			status = copy_line(data[fd], data[fd]->start + BUFF_SIZE, line);
			data[fd]->cur = NULL;
			return (status);
		}
		if (data[fd]->cur != data[fd]->start || nread == BUFF_SIZE) // buffer is not empty and contains no line
		{
			del = *line;
			*line = ft_strjoin(*line, data[fd]->cur);
			free(del);
			ft_bzero(data[fd]->start, BUFF_SIZE);
		}
		// buffer is empty
		nread = read(fd, data[fd]->start, BUFF_SIZE);
		if (nread == 0 && **line != '\0')
		{
			status = copy_line(data[fd], data[fd]->start + BUFF_SIZE, line);
			data[fd]->cur = NULL;
			return (status);
		}
		data[fd]->cur = data[fd]->start;
		if (nread < 1)
			return (nread);
	}
	// found a newline
	return (copy_line(data[fd], nl, line));
}
