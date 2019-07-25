/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:15:58 by vkarpova          #+#    #+#             */
/*   Updated: 2018/03/21 14:37:00 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_range(int min, int max)
{
	int		*str;
	int		i;
	int		m;

	m = min;
	i = 0;
	if (min >= max)
		return (NULL);
	str = (int*)malloc(sizeof(int) * (max - min + 1));
	while (m < max)
	{
		str[i] = m;
		m++;
		i++;
	}
	return (str);
}
