/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <vkarpova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:03:29 by vkarpova          #+#    #+#             */
/*   Updated: 2019/10/10 19:23:29 by nnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			num(char *str)
{
	int		i;

	i = 0;
	if (str)
	{
		if (str[i] == '-')
			i++;
		if (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			return (0);
		while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
			i++;
		if (str[i] == ']' || str[i] == ',')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

int			usage(int o)
{
	if (o == 1)
		ft_putendl("Something is wrong with file, try another one");
	else
		ft_putendl("	usage: ./RT [example_scene.json]");
	return (0);
}

int			parse_color(char *line, t_vector *vector)
{
	char	**name;
	char	**tmp;
	char	*test;
	char	*test1;
	char	*test2;

	name = ft_strsplit(line, ':');
	tmp = ft_strsplit(name[1], ',');
	test = ft_strtrim(tmp[0] + 1);
	test1 = ft_strtrim(tmp[1]);
	test2 = ft_strtrim(tmp[2]);
	if (num(tmp[0] + 1) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
	{
		vector->x = (double)(ft_atoi(test) / 255);
		vector->y = (double)(ft_atoi(test1) / 255);
		vector->z = (double)(ft_atoi(test2) / 255);
		free_n(12, test, test1, test2, tmp[0], tmp[1], tmp[2], tmp[3], tmp,
											name[0], name[1], name[2], name);
		return (1);
	}
	free_n(9, tmp[0], tmp[1], tmp[2], tmp[3], tmp, name[0], name[1],
											name[2], name);
	return (0);
}

void		free_n(int nbr, ...)
{
	int		i;
	va_list	list;

	i = 0;
	va_start(list, nbr);
	while (i < nbr)
	{
		free(va_arg(list, void *));
		i++;
	}
	va_end(list);
}

int			parse_vector(char *line, t_vector *vector)
{
	char	**name;
	char	**tmp;
	char	*test;
	char	*test1;
	char	*test2[2];

	name = ft_strsplit(line, ':');
	test2[1] = ft_strtrim(name[1]);
	tmp = ft_strsplit((test2[1]), ',');
	test = ft_strtrim(tmp[0] + 1);
	test1 = ft_strtrim(tmp[1]);
	test2[0] = ft_strtrim(tmp[2]);
	if (num(tmp[0] + 1) && num(tmp[1]) && num(tmp[2]) && tmp[3] == NULL)
	{
		vector->x = (double)ft_atoi(test);
		vector->y = (double)ft_atoi(test1);
		vector->z = (double)ft_atoi(test2[0]);
		free_n(13, test, test1, test2[0],
			test2[1], tmp[0], tmp[1], tmp[2], tmp[3],
								tmp, name[0], name[1], name[2], name);
		return (1);
	}
	free_n(9, tmp[0], tmp[1], tmp[2], tmp[3], tmp, name[0], name[1],
										name[2], name);
	return (0);
}
