/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 10:07:28 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/20 20:20:26 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include <printf.h>

static int	copy_line(t_buff *buff, char *nl, char *tmp, char **line)
{
	if (nl)
		*nl = '\0';
	if (tmp != NULL)
	{
		*line = ft_strjoin(tmp, buff->data);
		free(tmp);
	}
	else
		*line = ft_strdup(buff->cur);
	if (nl == NULL)
		return (0);
	buff->cur = nl + 1;
	return (1);
}

static int	fill_buff(int fd, t_buff *buff, char **line)
{
	char	*tmp;
	char	*tmp1;
	char	*nl;
	ssize_t	nread;
	ssize_t	tread;

	tmp = *line;
	tread = 0;
	while ((nread = read(fd, buff->data, BUFF_SIZE)) > 0)
	{
		tread += nread;
		if ((nl = ft_strchr(buff->data, '\n')))
			return (copy_line(buff, nl, tmp, line));
		if (tmp == NULL)
			tmp = ft_strdup(buff->data);
		else
		{
			tmp1 = tmp;
			tmp = ft_strjoin(tmp, buff->data);
			free(tmp1);
		}
	}
	if (tread && nread == 0)
		*line = tmp;
	return (tread >= 1 ? 1 : nread);
}

int			get_next_line(int fd, char **line)
{
	static t_buff	c = {{0}, c.data};
	char			*nl;

	if (fd < 0 || line == NULL || read(fd, c.data, 0) < 0)
		return (-1);
	if ((nl = ft_strchr(c.cur, '\n')))
		return (copy_line(&c, nl, NULL, line));
	if (c.cur != c.data)
	{
		*line = ft_strdup(c.cur);
		c.cur = c.data;
	}
	else
		*line = 0;
	ft_bzero(c.data, BUFF_SIZE);
	return (fill_buff(fd, &c, line));
}
