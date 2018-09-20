/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 10:07:28 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/19 23:56:29 by tkobb            ###   ########.fr       */
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
	ssize_t			nread;

	if ((nl = ft_strchr(c.cur, '\n')))
	{
		*line = alloc_line(c.cur, nl);
		c.cur = nl + 1;
		return (1);
	}
	if (c.cur != c.buf) // buf is not empty
	{
		*line = alloc_line(c.cur, c.buf + BUFF_SIZE);
	}
	while ((nread = read(fd, c.buf, BUFF_SIZE)) > 0)
	{
		if ((nl = ft_strchr(c.buf, '\n')))
		{
			*line = alloc_line(c.cur, nl);
			c.cur = nl + 1;
			return (1);	
		}
		return (-1); // buff too small
	}
	if (nread == -1)
		return (-1);
	return (0);
}
