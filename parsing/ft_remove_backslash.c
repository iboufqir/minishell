/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_backslash.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboufqir <iboufqir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:10:04 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/24 11:00:45 by iboufqir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_remove_backslash(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
			count++;
		else
			count++;
		i++;
	}
	return (count);
}

char	*ft_remove_backslash(char *str, t_var *var)
{
	int		i;
	int		j;
	char	backslash;
	char	*ptr;

	(1) && (i = 0, j = 0, backslash = 0);
	ptr = malloc((count_remove_backslash(str) + 1) * sizeof(char));
	if (!ptr)
		msg_error(-1, "Allocation Failed !!\n", var);
	while (str && str[i])
	{
		if (!backslash && str[i] == '\\'
			&& (str[i + 1] == '\'' || str[i + 1] == '\"'))
			backslash = str[i];
		else if (!backslash && str[0] == '\\' && str[i + 1] == '$')
			backslash = str[i];
		if (backslash == str[i])
			backslash = 0;
		else if (backslash != str[i])
			ptr[j++] = str[i];
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}
