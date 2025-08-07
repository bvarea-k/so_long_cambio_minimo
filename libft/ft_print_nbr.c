/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgo <bgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:10:35 by bvarea-k          #+#    #+#             */
/*   Updated: 2025/08/07 20:17:29 by bgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	ft_print_nbr(int n)
{
	char	c;
	int		result;

	result = 1;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		result++;
	}
	if (n > 9)
		result = result + ft_print_nbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
	return (result);
}*/

int	ft_print_nbr(int n)
{
	char	c;
	int		result;

	c = 0;
	result = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		result++;
	}
	if (n > 9)
		result += ft_print_nbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
	result++;
	return (result);
}


/*int	ft_print_nbr(int n)
{
	char	c;
	int		result;

	result = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		result += write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		result += ft_print_nbr(n / 10);
	c = (n % 10) + '0';
	result += write(1, &c, 1);
	return (result);
}*/

