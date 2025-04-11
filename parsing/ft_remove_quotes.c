/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboufqir <iboufqir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:51:52 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/24 10:59:43 by iboufqir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_cmd(char *str)
{
	int		i;
	int		count;
	char	check_quotes;

	(1) && (i = 0, count = 0, check_quotes = 0);
	while (str[i])
	{
		if (check_quotes == '\0' && i > 0 && \
		(str[i] == '\'' || str[i] == '\"') && str[i - 1] == '\\')
			(1) && (count++, i++);
		else if (check_quotes == '\0' && str[i] == '\\'
			&& (str[i + 1] == '\'' || str[i + 1] == '\"'))
			i++;
		else if (check_quotes == '\0' && str[i] == '$'
			&& (str[i + 1] == '\'' || str[i + 1] == '\"'))
			i++;
		else if (check_quotes == '\0' && (str[i] == '\"' || str[i] == '\''))
			check_quotes = str[i++];
		else if (check_quotes == str[i])
			(1) && (check_quotes = 0, i++);
		else if (check_quotes != str[i])
			(1) && (count++, i++);
	}
	return (count);
}

int	check_(char c1, char c2)
{
	if (c1 == '\\' && (c2 == '\'' || c2 == '\"'))
		return (1);
	else if (c1 == '$' && (c2 == '\'' || c2 == '\"'))
		return (1);
	return (0);
}

char	*ft_remove_quotes(char *str, t_var *var)
{
	char	*ptr;
	char	check_quotes;
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	ptr = ft_calloc((count_cmd(str) + 1), sizeof(char));
	if (!ptr)
		msg_error(-1, "Allocation Failed !!\n", var);
	while (str[i])
	{
		if (check_quotes == '\0' && i > 0
			&& (str[i] == '\'' || str[i] == '\"') && str[i - 1] == '\\')
			ptr[j++] = str[i++];
		else if (check_quotes == '\0' && check_(str[i], str[i + 1]))
			i++;
		else if (check_quotes == '\0' && (str[i] == '\"' || str[i] == '\''))
			check_quotes = str[i++];
		else if (check_quotes == str[i])
			(1) && (check_quotes = 0, i++);
		else if (check_quotes != str[i])
			ptr[j++] = str[i++];
	}
	return (ptr);
}
