/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 14:29:36 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/10 14:11:13 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (n < 0)
	{
		n = -n;
		i = 1;
	}
	while ((n / 10) > 0)
	{
		len++;
		n = n / 10;
	}
	return (len + i + 1);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		len;

	len = ft_count(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s[len] = '\0';
	if (n < 0)
		n = -n;
	while (--len > 0)
	{
		s[len] = n % 10 + '0';
		n = n / 10;
	}
	if (n > 0 && n <= 9)
		s[len] = n + '0';
	else if (n == 0 && s[1] == '\0')
		s[len] = '0';
	else
		s[len] = '-';
	return (s);
}
