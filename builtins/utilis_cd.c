/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:05:33 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/19 22:59:37 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_pwd(t_env **data_env, char *pwd, char *c, t_var *var)
{
	t_env	*env;
	char	*content;

	env = *data_env;
	while (env)
	{
		if (ft_strcmp(env->variable, pwd) == 0)
		{
			env->c = '=';
			free(env->content);
			if (!c)
			{
				content = ft_strjoin(env->content, "/..", var);
				env->content = ft_strdup(content, var);
				free(content);
			}
			else
				env->content = ft_strdup(c, var);
		}
		env = env->next;
	}
}

char	*ft_getenv(t_env **data_env, char *str)
{
	t_env	*current;

	current = *data_env;
	while (current)
	{
		if (ft_strcmp(current->variable, str) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}
