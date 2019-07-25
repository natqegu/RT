/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:15:46 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/12 12:29:52 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_list_push_front(t_list **begin_list, void *content)
{
	t_list	*list;
	t_list	*new;

	if (!*begin_list)
		*begin_list = ft_create_elem(content);
	else
	{
		new = *begin_list;
		list = ft_create_elem(content);
		*begin_list = list;
		list->next = new;
	}
}
