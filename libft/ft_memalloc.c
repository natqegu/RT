/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:59:11 by vkarpova          #+#    #+#             */
/*   Updated: 2018/03/30 19:56:34 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*new;
	int		i;

	i = 0;
	new = (void *)malloc(size);
	if (new == NULL)
		return (NULL);
	while (size > 0)
	{
		((unsigned char *)new)[i] = 0;
		i++;
		size--;
	}
	return (new);
}
