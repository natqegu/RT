/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:08:26 by vkarpova          #+#    #+#             */
/*   Updated: 2018/06/25 17:39:06 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		join_newbuf(char **all_buf, char *buf)
{
	char	*tmp_all;

	tmp_all = ft_strjoin(*all_buf, buf);
	free(*all_buf);
	*all_buf = tmp_all;
}

static int		find_enter(char **all_buf, char **line)
{
	char	*s;

	s = ft_strchr(*all_buf, '\n');
	if (s)
	{
		*s = '\0';
		*line = ft_strdup(*all_buf);
		ft_memmove(*all_buf, s + 1, ft_strlen(s + 1));
		ft_strclr(&all_buf[0][ft_strlen(s + 1)]);
		return (1);
	}
	*line = *all_buf;
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char	*all_buf[8192];
	char		buf[BUFF_SIZE + 1];
	int			ret;

	if (!line || fd < 0 || fd > 8192 || BUFF_SIZE <= 0)
		return (-1);
	ret = 1;
	while (ret > 0)
	{
		ft_bzero(buf, BUFF_SIZE + 1);
		ret = read(fd, buf, BUFF_SIZE);
		join_newbuf(&all_buf[fd], buf);
		if (all_buf[fd] && (find_enter(&all_buf[fd], line) == 1))
			return (1);
	}
	if (*all_buf[fd] != '\0')
	{
		all_buf[fd] = NULL;
		return (1);
	}
	return (ret);
}
