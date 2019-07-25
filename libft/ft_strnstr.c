/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:47:52 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/23 15:36:32 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n;

	n = 0;
	j = 0;
	while (big[j] != '\0')
	{
		i = 0;
		n = j;
		while (big[j] == little[i] && len > j && little[i] != '\0')
		{
			i++;
			j++;
		}
		if (little[i] == '\0')
			return ((char *)big + n);
		else
			j = n;
		j++;
	}
	return (0);
}
