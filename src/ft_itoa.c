/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:35:40 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/19 22:33:28 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_len_int(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	if (n == 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*ft_converter(int n, char *ptr)
{
	int		len_n;
	int		check_negative;

	check_negative = 0;
	len_n = ft_len_int(n) - 1;
	if (n < 0)
	{
		check_negative = 1;
		n *= -1;
		ptr[0] = '-';
	}
	while (len_n >= check_negative)
	{
		ptr[len_n] = n % 10 + 48;
		n /= 10;
		len_n--;
	}
	return (ptr);
}

char	*ft_itoa(int n, t_var *var)
{
	char	*ptr;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648", var));
	len = ft_len_int(n);
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		msg_error(-1, "Allocation Failed !!", var);
	ptr = ft_converter(n, ptr);
	return (ptr);
}
