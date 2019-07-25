/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:12:36 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/12 12:26:41 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_create_elem(void *content)
{
	t_list	*list;

	list = (t_list*)malloc(sizeof(t_list));
	if (list)
	{
		list->content = content;
		list->next = NULL;
	}
	return (list);
}
