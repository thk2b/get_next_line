/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 10:07:28 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/19 12:42:29 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

static char	*find_nl(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
		if (s[i] == '\n')
			return ((char*)s + i);
		else
			i++;
	if (s[i] == '\0')
		return ((char*)s + i);
	return (NULL);
}

static char *alloc_line(const char *start, const char *end)
{
	char	*l;
	size_t	len;

	len = end - start;
	if ((l = (char*)malloc(len * sizeof(char))) == NULL)
		return (NULL);
	return (ft_strncpy(l, start, len + 1));
	return (l);
}

int		get_next_line(int fd, char **line)
{
	static char *buf; // current start of buffer
	char		*el; // current end of line
	char		*tmp;
	char		*tmp1;
	int			status;
	
	el = find_nl(buf);
	if (el == NULL)
		if ((buf = (char*)malloc(BUFF_SIZE * sizeof(char))) == NULL)
			return (-1);
	while (el == NULL && (status = read(fd, (void*)buf, BUFF_SIZE)) > 0)
		if ((el = find_nl(buf)) == NULL)
		{ // keep reading
			tmp1 = tmp;
			free(tmp);
			tmp = ft_strjoin(tmp1, buf);
		}
	if (status == -1)
		return (-1);
	*line = alloc_line(buf, el);
	buf = el;
	if (*el == '\0')
	{ // EOF
		free(buf);
		return (0);
	}	
	return (1);
}
