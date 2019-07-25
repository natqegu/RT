/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:40:11 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/19 17:30:31 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	if (!dst && !src && !n)
		return (NULL);
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	while (n > i)
	{
		d[i] = s[i];
		if (d[i] == (unsigned char)c)
			return (d + i + 1);
		i++;
	}
	return (NULL);
}
