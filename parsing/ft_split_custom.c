/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_custom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:30:42 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/17 20:05:27 by ahomari          ###   ########.fr       */
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

static int	ft_count_word(char *str)
{
	int	i;
	int	count;
	int	check;

	(1) && (i = 0, count = 0, check = 0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && check == 0)
		{
			check = 1;
			count++;
		}
		else if (str[i] == ' ' || str[i] == '\t')
			check = 0;
		i++;
	}
	return (count);
}

static char	**ft_print(char **ptr, char *s, t_var *v)
{
	(1) && (v->i = 0, v->j = 0, v->single = 0);
	while (s[v->i])
	{
		while (s[v->i] && (s[v->i] == ' ' || s[v->i] == '\t') && !v->single)
			v->i++;
		if (!s[v->i])
			break ;
		v->start = v->i;
		while (s && s[v->i])
		{
			if (s[v->i] && !v->single && (s[v->i] == '\'' || s[v->i] == '\"'))
				v->single = s[v->i];
			else if (s[v->i] && v->single && s[v->i] == v->single)
				v->single = '\0';
			if (!s[v->i] || ((s[v->i] == ' ' || s[v->i] == '\t') && !v->single))
				break ;
			v->i++;
		}
		v->end = v->i;
		ptr[v->j] = ft_substr(s, v->start, v->end - v->start, v);
		if (!(ptr[v->j]))
			return (ft_free(ptr, v->j));
		v->j++;
	}
	return (ptr);
}

char	**ft_split_custom(char *s, t_var *var)
{
	char	**ptr;
	char	*str;

	if (!s)
		return (NULL);
	str = add_space(s, var);
	ptr = ft_calloc((ft_count_word(str) + 1), sizeof(char *));
	if (!ptr)
		msg_error(-1, "Allocation Failed !!\n", var);
	ptr = ft_print(ptr, str, var);
	free(str);
	str = NULL;
	return (ptr);
}
