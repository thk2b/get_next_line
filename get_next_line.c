/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 10:07:28 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/19 23:30:21 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

static char	*alloc_line(const char *start, const char *end)
{
	size_t	len;
	char *s;

	len = end - start;
	if((s = (char*)malloc(len * sizeof(char))) == NULL)
		return (NULL);
	ft_memcpy(s, start, len);
	s[len] = '\0';
	return (s);
}

int		get_next_line(int fd, char **line)
{
	static t_buff	c = {
		{0},
		c.buf + BUFF_SIZE,
		c.buf
	};
	char			*nl;
	char			*tmp = NULL;
	char			*tmptmp;
	ssize_t			toread;
	ssize_t			nread;
	size_t			len;
	ssize_t			totalread;

	if ((nl = ft_strchr(c.cur, '\n')))
	{
		*line = alloc_line(c.cur, nl);
		c.cur = nl + 1;
		return (1);
	}
	// no newline found
	if (c.cur == c.buf) // buffer is empty
		toread = BUFF_SIZE;
	else // no newline
	{
		len = c.end - c.cur;
		ft_memmove(c.buf, c.cur, len);
		toread = BUFF_SIZE - len;
		c.cur = c.buf + len;
	}
	totalread = 0;
	while ((nread = read(fd, c.cur, toread)) > 0)
	{
		totalread += nread;
		if((nl = ft_strchr(c.cur, '\n')))
		{
			*line = alloc_line(c.cur, nl);
			c.cur = nl + 1;
			return (1);
		}
		// buffer is full and has no newline
		tmptmp = tmp;
		tmp = ft_strjoin(tmp, c.buf);
		free(tmptmp);
		toread = BUFF_SIZE;
	}
	if (nread == -1)
		return (-1);
	if (nread == 0)
		return (0);
	*line = alloc_line(tmp, tmp + totalread);
	c.cur = nl + 1;
	return (1);
}
