/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 22:41:11 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/21 14:18:38 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <unistd.h>

static	int	copy_line(t_buff *data, char *end, char **dst)
{
	
}

static int	fill_buff(t_buff *data, char **dst)
{

}

int		get_next_line(int fd, char **line)
{
	static t_buff	*data[256] = {NULL};
	char			*nl;

	if (data[fd] == NULL) // no t_buff
		ALLOC_CHECK(data[fd] = (t_buff*)malloc(sizeof(t_buff)));
	else if (data[fd]->start == NULL) // no t_buff data memory
	{
		ALLOC_CHECK(data[fd]->start = (char*)malloc(BUFF_SIZE + 1));
		data[fd]->cur = data[fd]->start;
		bzero(data[fd]->start, BUFF_SIZE + 1);
	}
	else if (data[fd]->cur == NULL) // reached OEF
		return (0);
	if ((nl = ft_strchr(data[fd]->cur, '\n'))) // buffer contains a line
		return (copy_line(data[fd], nl, line));
	if (data[fd]->cur != data[fd]->start) // buffer is not empty and contains no line
		;
	return (fill_buff(data[fd], line));
}
