/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboufqir <iboufqir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:33:20 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/24 10:56:40 by iboufqir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_sub(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			count += 2;
		else
			count += 1;
		i++;
	}
	return (count);
}

int	count_s(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' && str[i + 1] == '$')
			count += 2;
		else
			count += 1;
		i++;
	}
	return (count);
}

void	change_value_env(t_env **env, char **cmd, int flag, t_var *var)
{
	t_env	*current;
	int		i;

	i = 0;
	current = *env;
	while (cmd && cmd[i + 1])
		i++;
	while (current)
	{
		if (ft_strcmp(current->variable, "_") == 0)
		{
			free(current->content);
			if (flag == 0)
				current->content = ft_strdup(cmd[i], var);
			else
				current->content = ft_strdup("", var);
		}
		current = current->next;
	}
}

void	get_env(char **env, t_env **s_env, t_var *var)
{
	int		i;
	char	*content;
	char	*variable;
	char	**ptr;

	i = 0;
	while (env && env[i])
	{
		ptr = ft_split(env[i], '=', var);
		content = ptr[1];
		variable = ptr[0];
		var->c = check_value(env[i]);
		lstadd_env(s_env, content, variable, var);
		(free(content), free(variable), free(ptr));
		i++;
	}
}

void	ft_empty_env(t_env **s_env, t_var *var)
{
	char	**env;
	char	*cwd;

	env = malloc(7 * sizeof(char *));
	if (!env)
		msg_error(-1, "Allocation Failed !!\n", var);
	cwd = getcwd(NULL, 0);
	env[0] = ft_strdup("OLDPWD", var);
	env[1] = ft_strjoin("PWD=", cwd, var);
	free(cwd);
	env[2] = ft_strdup("SHLVL=1", var);
	env[3] = ft_strdup("_=/usr/bin/env", var);
	env[4] = ft_strdup("PATH=/Users/ahomari/goinfre/homebrew/bin:"\
			"/Users/ahomari/.brew/bin:/usr/local/bin:"\
			"/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:"\
			"/Library/Apple/usr/bin", var);
	env[5] = NULL;
	get_env(env, s_env, var);
	free_list(env);
}
