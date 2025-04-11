/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:37:36 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/24 11:44:28 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*return_value_(char *str, t_var *var)
{
	int		i;
	int		j;
	char	*ptr;

	(1) && (i = 0, j = 0, ptr = 0);
	ptr = malloc((count_sub(str) + 1) * sizeof(char));
	if (!ptr)
		msg_error(-1, "Allocation Failed !!\n", var);
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ptr[j++] = '\\';
			ptr[j++] = str[i];
		}
		else
			ptr[j++] = str[i];
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*return_value(t_var *var, char *str, t_env *s_env)
{
	t_env	*current;
	char	*status;
	char	*ptr;

	current = s_env;
	while (current)
	{
		if (ft_strcmp(current->variable, str + 1) == 0)
		{
			ptr = return_value_(current->content, var);
			return (ptr);
		}
		current = current->next;
	}
	if (str && str[1] == '?')
	{
		status = ft_itoa(exit_stat(0, 1), var);
		ptr = ft_strjoin(status, str + 2, var);
		free(status);
		return (ptr);
	}
	return (ft_strdup("", var));
}

char	*ft_expand_replace(char *str, t_var *var, t_env *s_env)
{
	char	*ptr;
	char	*join;
	char	*tab[3];

	tab[0] = ft_substr(str, 0, var->start, var);
	tab[1] = ft_substr(str, var->start, var->end - var->start, var);
	tab[2] = ft_substr(str, var->end, ft_strlen(str), var);
	ptr = return_value(var, tab[1], s_env);
	join = ft_strjoin(tab[0], ptr, var);
	free(ptr);
	ptr = ft_strjoin(join, tab[2], var);
	(free(tab[0]), free(tab[1]), free(tab[2]));
	free(join);
	return (ptr);
}

int	ft_check_expand(char *str, int flag)
{
	int		i;
	char	single;

	i = 0;
	single = 0;
	while (str && str[i])
	{
		if (i > 0 && !single
			&& (str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\')
			single = str[i];
		else if (i == 0 && !single && (str[i] == '\'' || str[i] == '\"'))
			single = str[i];
		else if (single && str[i] == single && str[i - 1] != '\\')
			single = '\0';
		else if (str[i] == '\\' && str[i + 1] == '$')
			return (-1);
		else if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?' \
		|| str[i + 1] == '_') && ((single == '\'' && flag) || single == '\"' \
		|| single == 0))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_expand(char *str, t_var *var, t_env *s_env, int flag)
{
	char	*ptr;

	var->end = 0;
	var->start = ft_check_expand(str, flag);
	if (var->start != -1)
	{
		var->end = var->start + 1;
		if (ft_isdigit(str[var->end]) || str[var->end] == '?' \
		|| (str[var->end] == '_' && str[var->end + 1] != '_' ))
		{
			var->end++;
			ptr = ft_expand_replace(str, var, s_env);
		}
		else
		{
			while (str && (ft_isalnum(str[var->end]) || str[var->end] == '_'))
				var->end++;
			ptr = ft_expand_replace(str, var, s_env);
		}
		if (ft_check_expand(ptr, flag) != -1)
			return (str = ft_expand(ptr, var, s_env, flag), free(ptr), str);
		return (ptr);
	}
	ptr = value_(str, var);
	return (ptr);
}
