/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:23:46 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/11 16:58:36 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char *s, char c)
{
	int		w;
	int		i;

	w = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if ((s[i] == c && s[i] != '\0') || (s[i] == '\0' && s[i - 1] != c))
			w++;
		if (s[i] == '\0')
			return (w);
		i++;
	}
	return (w);
}

static int	ft_letters(char *s, char c)
{
	int		l;
	int		i;

	i = 0;
	l = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	if (s[i] != '\0')
	{
		while (s[i] != c && s[i] != '\0')
		{
			l++;
			i++;
		}
	}
	return (l);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**new;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (!s || c == 0)
		return (0);
	new = (char **)malloc(sizeof(char *) * (ft_words((char *)s, c) + 1));
	if (new == NULL)
		return (NULL);
	while (s[k] != '\0')
	{
		if (ft_letters(((char *)s + k), c) == 0)
			break ;
		while (s[k] == c && s[k] != '\0')
			k++;
		new[j] = ft_strsub((s + k), 0, ft_letters((char *)s + k, c));
		k = k + ft_strlen(new[j]);
		j++;
	}
	new[j] = NULL;
	return (new);
}
