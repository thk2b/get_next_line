/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 22:41:11 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/21 16:18:53 by tkobb            ###   ########.fr       */
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
	b->start = NULL;
	return (b);
}

static	int	copy_line(t_buff *data, char *end, char **dst)
{
	*end = '\0';
	ALLOC_CHECK(*dst = ft_strjoin(*dst, ft_strsub(data->cur, 0, end - data->cur))); //leaks
	return (1);
}

// static int	fill_buff(t_buff *data, char **dst)
// {

// }
#include <printf.h>
int		get_next_line(int fd, char **line)
{
	static t_buff	*data[256] = {NULL};
	char			*nl;
	ssize_t			nread;
	ssize_t			pread;
	int				status;

	if (data[fd] == NULL) // no t_buff
	{
		ALLOC_CHECK(data[fd] = buff_new());
	}
	if (data[fd]->start == NULL) // no t_buff data memory
	{
		ALLOC_CHECK(data[fd]->start = (char*)malloc(BUFF_SIZE + 1));
		data[fd]->cur = data[fd]->start;
		ft_bzero(data[fd]->start, BUFF_SIZE + 1);
	}
	else if (data[fd]->cur == NULL) // reached OEF
		return (0);
	ALLOC_CHECK(*line = ft_strdup(""));
	nread = 0;
	while ((nl = ft_strchr(data[fd]->cur, '\n')) == NULL)
	{
		// printf("%zd", nread);
		if (nread > 0 && nread != BUFF_SIZE) // didn't find a newline but cound not read whole buffer: reached EOF
		{
			status = copy_line(data[fd], data[fd]->start + BUFF_SIZE, line);
			data[fd]->cur = NULL;
			return (status);
		}
		if (data[fd]->cur != data[fd]->start || nread == BUFF_SIZE) // buffer is not empty and contains no line
		{
			*line = ft_strjoin(*line, data[fd]->cur); //leaks
		}
		// buffer is empty
		ft_bzero(data[fd]->cur, BUFF_SIZE);
		pread = nread;
		nread = read(fd, data[fd]->start, BUFF_SIZE);
		if (pread == BUFF_SIZE && nread == 0) // previeously read a full buffer, but nothing now
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
