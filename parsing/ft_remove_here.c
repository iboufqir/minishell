/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:36:54 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/15 13:51:45 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_cmd_here(char *str)
{
	int		i;
	int		count;
	char	check_quotes;

	i = 0;
	count = 0;
	check_quotes = 0;
	if (str[i] == '$' && (str[i + 1] == '\"' || str[i + 1] == '\''))
		i++;
	while (str[i])
	{
		if (check_quotes == '\0' && (str[i] == '\'' || str[i] == '\"'))
			check_quotes = str[i];
		else if (check_quotes == str[i])
			check_quotes = 0;
		else if (check_quotes != str[i])
			count++;
		i++;
	}
	return (count);
}

char	*ft_remove_here(char *str, t_var *var)
{
	char	*ptr;
	char	check_quotes;
	int		count;
	int		i;
	int		j;

	(1) && (i = 0, j = 0, check_quotes = 0);
	count = count_cmd_here(str);
	ptr = malloc((count + 1) * sizeof(char));
	if (!ptr)
		msg_error(-1, "Allocation Failed !!\n", var);
	if (str[i] == '$' && (str[i + 1] == '\"' || str[i + 1] == '\''))
		i++;
	while (str[i])
	{
		if (check_quotes == '\0' && (str[i] == '\'' || str[i] == '\"'))
			check_quotes = str[i];
		else if (check_quotes == str[i])
			check_quotes = 0;
		else if (check_quotes != str[i])
			ptr[j++] = str[i];
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}
