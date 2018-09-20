/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 10:05:23 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/19 23:31:47 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1024

typedef struct	s_buff
{
	char	buf[BUFF_SIZE];
	char	*end;
	char	*cur;
}				t_buff;

int		get_next_line(int fd, char **line);

#endif
