/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 13:28:58 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/12 17:15:26 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*func;

	if (!lst || !f)
		return (NULL);
	func = (t_list *)malloc(sizeof(t_list));
	if (!func)
		return (NULL);
	new = f(lst);
	func = new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = f(lst);
		if ((new->next = f(lst)) == NULL)
		{
			free(new->next);
			return (NULL);
		}
		new = new->next;
	}
	return (func);
}
