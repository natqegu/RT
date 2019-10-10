/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 21:52:17 by vkarpova          #+#    #+#             */
/*   Updated: 2019/09/29 21:52:18 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

char		**get_scene(char *buf, int lines)
{
	int		i;
	int		k;
	int		j;
	char	**data;

	k = 0;
	j = 0;
	if (!buf || (!(data = (char **)malloc(sizeof(char *) * (lines + 1)))))
		return (0);
	while (buf[k] != '\0' && j < lines)
	{
		i = 0;
		if (!(data[j] = ft_strnew(ft_linelen(buf, k))))
			return (0);
		while (buf[k] != '\n' && buf[k] != '\0')
		{
			data[j][i++] = buf[k++];
		}
		data[j][i] = '\0';
		k++;
		j++;
	}
	data[j] = NULL;
	free(buf);
	return (data);
}

void		open_2(int lines, char *buf, t_global *g)
{
	char	**data;
	int		kk;

	kk = 0;
	if (!(data = get_scene(buf, lines)))
		data = NULL;
	parse_file(g, data, lines);
	while (data[kk] != NULL)
		free(data[kk++]);
	free(data);
}

int			open_file(char **argv, t_global *g)
{
	int		fd;
	char	*line;
	char	*buf;
	int		lines;

	fd = open(argv[1], O_RDONLY);
	buf = ft_strnew(1);
	if (argv[0][0] != '.' || argv[0][1] != '/')
		return (0);
	if (fd == -1)
		return (0);
	lines = 0;
	while (get_next_line(fd, &line))
	{
		buf = ft_strjoin_fake(buf, ft_strjoin_fake(
					ft_strtrim(line), "\n", 'l'), 'b');
		free(line);
		lines++;
	}
	free(line);
	open_2(lines, buf, g);
	close(fd);
	return (1);
}

int			count_objects(t_global *g, int fd)
{
	char	*line;
	char	buff[8];

	g->lights = 0;
	if (read(fd, buff, 8) < 8)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strnstr(line, "PLANE", 25) || ft_strnstr(line, "CONE", 25) ||
			ft_strnstr(line, "CYLINDER", 25) || ft_strnstr(line, "TRI", 25) ||
			ft_strnstr(line, "SPHERE", 25) || ft_strnstr(line, "COMPLEX", 25))
			g->argc++;
		if (ft_strnstr(line, "LIGHT", 25))
			g->lights++;
		free(line);
	}
	free(line);
	return (g->argc);
}

int			check_arg(char **argv, int argc, t_global *g)
{
	int		fd;

	if (argc != 2)
		return (usage(0));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1 || (argv[1][0] == '.' && argv[1][1] == '/')
									|| !count_objects(g, fd))
	{
		usage(1);
		return (0);
	}
	close(fd);
	if (!open_file(argv, g))
	{
		usage(1);
		return (0);
	}
	ginit(g);
	return (1);
}
