/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 13:50:33 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/19 17:50:04 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_find(const char *big, const char *little)
{
	int			i;
	int			j;
	int			a;

	i = 0;
	j = 0;
	while (big[i] != '\0')
	{
		j = 0;
		a = i;
		while (big[i] == little[j] && little[j] != '\0')
		{
			i++;
			j++;
		}
		if (little[j] == '\0')
			return ((char *)big + a);
		else
			i = a;
		i++;
	}
	return (0);
}

char			*ft_strstr(const char *big, const char *little)
{
	if (little[0] == '\0')
		return ((char *)big);
	else
		return (ft_find(big, little));
}
