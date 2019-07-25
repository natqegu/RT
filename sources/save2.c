/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:28:18 by vkarpova          #+#    #+#             */
/*   Updated: 2019/02/01 17:28:18 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				save_color(t_all *all, int *color)
{
	char		*line;
	t_vector	c;
	char		**tmp;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strncmp(line, "-color:", 7) == 0))
	{
		tmp = ft_strsplit(&line[7], ',');
		free(line);
		if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
		{
			c.x = (double)ft_atoi(tmp[0]);
			c.y = (double)ft_atoi(tmp[1]);
			c.z = (double)ft_atoi(tmp[2]);
			*color = rgb_to_int(c);
			free(tmp[1]);
			free(tmp[2]);
			free(tmp);
			free(*tmp);
			return (1);
		}
	}
	return (0);
}

int				save_normal(t_all *all, t_vector *norm)
{
	char		**tmp;
	char		*line;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strncmp(line, "-normal:", 8) == 0))
	{
		tmp = ft_strsplit(&line[8], ',');
		free(line);
		if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
		{
			norm->x = (double)ft_atoi(tmp[0]);
			norm->y = (double)ft_atoi(tmp[1]);
			norm->z = (double)ft_atoi(tmp[2]);
			free(tmp[1]);
			free(tmp[2]);
			free(tmp);
			free(*tmp);
			return (1);
		}
	}
	return (0);
}

int				save_center(t_all *all, t_vector *center)
{
	char		**tmp;
	char		*line;

	if ((get_next_line(all->fd, &line) > 0) &&
		(ft_strncmp(line, "-center:", 8) == 0))
	{
		tmp = ft_strsplit(&line[8], ',');
		free(line);
		if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
		{
			center->x = (double)ft_atoi(tmp[0]);
			center->y = (double)ft_atoi(tmp[1]);
			center->z = (double)ft_atoi(tmp[2]);
			free(tmp[1]);
			free(tmp[2]);
			free(tmp);
			free(*tmp);
			return (1);
		}
	}
	return (0);
}

void			save_cam(char *line, t_all *all)
{
	char		**tmp;

	tmp = ft_strsplit(&line[7], ',');
	if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
	{
		all->cam.x = (double)ft_atoi(tmp[0]);
		all->cam.y = (double)ft_atoi(tmp[1]);
		all->cam.z = (double)ft_atoi(tmp[2]);
		all->is_cam = 1;
	}
	else
	{
		all->cam.x = 0;
		all->cam.y = 0;
		all->cam.z = -30;
		ft_putendl("Incorrect info for #camera, so I set it to (0,0,-30)");
	}
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	free(*tmp);
}

void			save_rotation(t_all *all, char *line)
{
	char		**tmp;

	tmp = ft_strsplit(&line[9], ',');
	if (num(tmp[0]) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
	{
		all->rot.x = (double)ft_atoi(tmp[0]);
		all->rot.y = (double)ft_atoi(tmp[1]);
		all->rot.z = (double)ft_atoi(tmp[2]);
	}
	else
	{
		all->rot = init_vector(0, 0, 0, 0);
		ft_putendl("Incorrect info for #rotation, so I set it to (0,0,0)");
	}
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	free(*tmp);
}
