/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:55:56 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/03 15:38:24 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*a;
	int		i;

	i = 0;
	if (s && f)
	{
		while (s[i] != '\0')
			i++;
		a = (char *)malloc(sizeof(char) * (i + 1));
		if (a == NULL)
			return (NULL);
		i = 0;
		while (s[i] != '\0')
		{
			a[i] = f(s[i]);
			i++;
		}
		a[i] = '\0';
		return (a);
	}
	return (0);
}
