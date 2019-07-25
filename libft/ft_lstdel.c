/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 11:34:59 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/12 14:33:42 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (alst && del)
	{
		while ((*alst))
		{
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			(*alst) = (*alst)->next;
		}
		*alst = NULL;
	}
}
