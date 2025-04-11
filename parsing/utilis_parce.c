/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_parce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboufqir <iboufqir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:43:01 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/24 11:01:39 by iboufqir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*ft_malloc(t_var *var)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		msg_error(-1, "Allocation Failed !!\n", var);
	ft_memset(new, 0, sizeof(t_command));
	return (new);
}

int	ft_check(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		else if (str[i] != c)
			break ;
		i++;
	}
	return (count);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

char	*value_(char *str, t_var *var)
{
	int		i;
	int		j;
	char	*ptr;

	(1) && (i = 0, j = 0, ptr = 0);
	ptr = malloc((count_s(str) + 1) * sizeof(char));
	if (!ptr)
		msg_error(-1, "Allocation Failed !!\n", var);
	while (str && str[i])
	{
		if (str[i] == '\'' && str[i + 1] == '$')
		{
			ptr[j++] = str[i++];
			ptr[j++] = '\\';
			ptr[j++] = str[i++];
		}
		else
			ptr[j++] = str[i++];
	}
	ptr[j] = '\0';
	return (ptr);
}
