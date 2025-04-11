/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:36:49 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/17 18:08:37 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_realloc(char **ptr, char *str, size_t new_size, t_var *var)
{
	char	**new_ptr;
	size_t	i;

	i = 0;
	new_ptr = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!new_ptr)
		msg_error(-1, "Allocation Failed !!\n", var);
	while (ptr && ptr[i])
	{
		new_ptr[i] = ptr[i];
		ptr[i] = NULL;
		i++;
	}
	new_ptr[i++] = ft_strdup(str, var);
	new_ptr[i] = 0;
	free(ptr);
	return (new_ptr);
}
