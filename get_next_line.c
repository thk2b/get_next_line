/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 10:07:28 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/20 17:57:04 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

static int	copy_line(t_buff *buff, char *nl, char *tmp, char **line)
{
	*nl = '\0';
	if (tmp != NULL)
	{
		*line = ft_strjoin(tmp, buff->data);
		free(tmp);
	}
	else
		*line = ft_strdup(buff->cur);
	buff->cur = nl + 1;
	return (1);
}

static int	fill_buff(int fd, t_buff *buff, char **line)
{
	char	*tmp;
	char	*tmp1;
	char	*nl;
	ssize_t	nread;

	tmp = *line;
	while ((nread = read(fd, buff->data, BUFF_SIZE)) > 0)
	{
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
	return (nread);
}

int			get_next_line(int fd, char **line)
{
	static t_buff	c = {{0}, c.data};
	char			*nl;

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
