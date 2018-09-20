/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 10:05:23 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/20 12:50:44 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 3

typedef struct	s_buff
{
	char	data[BUFF_SIZE + 1];
	char	*cur;
}				t_buff;

int		get_next_line(int fd, char **line);

#endif
