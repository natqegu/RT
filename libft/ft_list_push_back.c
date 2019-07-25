/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:14:32 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/16 14:51:04 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_list_push_back(t_list **begin_list, void *content)
{
	t_list	*tmp;

	if (begin_list)
	{
		tmp = *begin_list;
		if (!tmp)
			*begin_list = ft_create_elem(content);
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = ft_create_elem(content);
		}
	}
}
