/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:22:17 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/23 14:32:52 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	a;
	size_t			i;

	i = 0;
	a = (unsigned char)c;
	str = (unsigned char *)s;
	while (n > i)
	{
		if (str[i] == a)
			return (str + i);
		i++;
	}
	return (0);
}
