/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:28:40 by ahomari           #+#    #+#             */
/*   Updated: 2024/05/17 11:35:43 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	r;
	size_t			i;

	ptr = (unsigned char *)b;
	r = (unsigned char)c;
	i = 0;
	while (len > i)
	{
		ptr[i] = r;
		i++;
	}
	return ((void *)ptr);
}
