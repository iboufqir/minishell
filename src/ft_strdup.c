/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 00:31:01 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/15 14:02:19 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup(char *s1, t_var *var)
{
	char	*ptr;

	ptr = ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (!ptr)
		msg_error(-1, "Allocation Failed !!", var);
	ft_memcpy(ptr, s1, ft_strlen(s1));
	return (ptr);
}
