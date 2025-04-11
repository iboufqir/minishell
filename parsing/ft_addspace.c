/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:37:32 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/15 13:58:47 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_token(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "<", 1) == 0
		|| ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, "|", 1) == 0)
		return (1);
	return (0);
}

int	count_word(char *str)
{
	int	i;
	int	t;
	int	count;

	(1) && (i = 0, t = -1, count = ft_strlen(str));
	while (str && str[i])
	{
		t = is_token(str + i);
		if (t != 0)
		{
			if (i != 0 && is_space(str[i - 1]) == 0)
				count++;
			if (is_space(str[i + t]) == 0 && str[i + t] != '\0')
				count++;
			i += t - 1;
		}
		i++;
	}
	return (count);
}

void	check_quotes_(char c, int *check)
{
	if (c == '\'' || c == '\"')
	{
		if (*check == 0)
			*check = 1;
		else
			*check = 0;
	}
}

char	*more_addspace(char *ptr, char *str)
{
	int	check;
	int	i;
	int	j;
	int	t;

	(1) && (i = 0, j = 0, t = 0, check = 0);
	while (str && str[i])
	{
		t = is_token(str + i);
		check_quotes_(str[i], &check);
		if (t)
		{
			if (i != 0 && is_space(str[i - 1]) == 0 && check == 0)
				ptr[j++] = ' ';
			while (t-- > 0)
				ptr[j++] = str[i++];
			if (!str[i])
				break ;
			if (is_space(str[i]) == 0 && is_token(str + i) == 0 && check == 0)
				ptr[j++] = ' ';
		}
		else
			ptr[j++] = str[i++];
	}
	return (ptr);
}

char	*add_space(char *str, t_var *var)
{
	int		count;
	char	*ptr;

	count = count_word(str) + 1;
	ptr = ft_calloc(count, sizeof(char));
	if (!ptr)
		msg_error(-1, "Allocation Failed !!\n", var);
	ptr = more_addspace(ptr, str);
	return (ptr);
}
