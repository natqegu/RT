/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:06:13 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/11 17:28:41 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*new;
	int		j;

	if (!s)
		return (0);
	while ((*s == ' ' || *s == '\n' || *s == '\t') && *s != '\0')
		s++;
	if (*s == '\0')
		return (ft_strsub(s, 0, 0));
	j = ft_strlen(s) - 1;
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && j > 0)
		j--;
	new = ft_strsub(s, 0, j + 1);
	return (new);
}
