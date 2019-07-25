/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkarpova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:53:30 by vkarpova          #+#    #+#             */
/*   Updated: 2018/04/11 13:34:48 by vkarpova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd > 0)
	{
		if (n == -2147483648)
		{
			n = n % 1000000000;
			n = -n;
			ft_putchar_fd('-', fd);
			ft_putchar_fd('2', fd);
		}
		if (n < 0 && n != -2147483648)
		{
			n = -n;
			ft_putchar_fd('-', fd);
		}
		if (n < 10)
			ft_putchar_fd(n + '0', fd);
		else
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putchar_fd(n % 10 + '0', fd);
		}
	}
}
