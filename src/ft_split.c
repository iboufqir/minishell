/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:14:50 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/15 14:02:07 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static int	ft_count_word(char *str, char c)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	check = 0;
	while (str[i])
	{
		if (str[i] != c && str[i] != '\t' && check == 0)
		{
			check = 1;
			count++;
		}
		else if (str[i] == c || str[i] == '\t')
			check = 0;
		i++;
	}
	return (count);
}

static char	**ft_print(char **ptr, char *s, char c, t_var *var)
{
	int		start;
	size_t	end;
	int		j;

	end = 0;
	j = 0;
	start = -1;
	while (end <= ft_strlen(s))
	{
		if (s[end] != c && s[end] != '\t' && start < 0)
			start = end;
		else if ((s[end] == c || s[end] == '\t'
				|| end == ft_strlen(s)) && start >= 0)
		{
			ptr[j] = ft_substr(s, start, end - start, var);
			if (!(ptr[j]))
				return (ft_free(ptr, j));
			start = -1;
			j++;
		}
		end++;
	}
	return (ptr);
}

char	**ft_split(char *s, char c, t_var *var)
{
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = ft_calloc((ft_count_word(s, c) + 1), sizeof(char *));
	if (!ptr)
		msg_error(-1, "Allocation Failed !!\n", var);
	ptr = ft_print(ptr, s, c, var);
	return (ptr);
}
