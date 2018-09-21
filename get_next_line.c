/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 22:41:11 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/20 22:48:21 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <unistd.h>

int		get_next_line(int fd, char **line)
{
	static char	**buf = NULL;
	char		tmp[BUFF_SIZE + 1];
	size_t		nr;

	if (buf && *buf)
	{
		*line = *buf++;
		return (1);
	}
	if ((nr = read(fd, tmp, BUFF_SIZE)) < 1)
	{
		if (nr == 0)
			return (0);
		return (-1);
	}
	buf = ft_strsplit(tmp, '\n');
	*line = *buf++;
	return (1);
}
