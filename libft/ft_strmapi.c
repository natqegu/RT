/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 17:32:51 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/03 16:08:58 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			a[i] = f(i, s[i]);
			i++;
		}
		a[i] = '\0';
		return (a);
	}
	return (0);
}
