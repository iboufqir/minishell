/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:48:24 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/15 15:27:18 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_var_env(t_env *env, char *cmd, t_var *s_var)
{
	t_env	*tmp;
	char	*var;

	tmp = env;
	var = get_var(cmd, s_var);
	while (tmp)
	{
		if (ft_strcmp(tmp->variable, var) == 0)
		{
			free(var);
			return (0);
		}
		tmp = tmp->next;
	}
	free(var);
	return (1);
}

void	change_value(t_env **env, t_var *var, int add)
{
	t_env	*current;
	char	*ptr;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->variable, var->var) == 0)
		{
			free(current->content);
			if (!check_value(current->variable))
				current->c = '=';
			if (add == 1)
			{
				ptr = ft_strjoin(current->content, var->value, var);
				current->content = ft_strdup(ptr, var);
				free(ptr);
			}
			else
				current->content = ft_strdup(var->value, var);
		}
		current = current->next;
	}
}

void	ft_export(t_env *env, int *flag, t_var *var)
{
	while (env)
	{
		if (!var->empty)
			ft_print_export(env->variable, env->content, env->c);
		else if (var->empty && ft_strcmp(env->variable, "PATH") != 0 \
		&& ft_strcmp(env->variable, "_") != 0)
			ft_print_export(env->variable, env->content, env->c);
		env = env->next;
	}
	exit_stat(0, 0);
	*flag = -1;
}

void	ft_expo_env(t_env *env, char *cmd, int *flag, t_var *s_var)
{
	int		add;

	s_var->var = get_var(cmd, s_var);
	s_var->value = get_value(cmd, s_var);
	if (!check_var_env(env, cmd, s_var) && check_value(cmd))
	{
		exit_stat(0, 0);
		*flag = -1;
		add = 0;
		if (check_plus(cmd))
			add = 1;
		change_value(&env, s_var, add);
	}
	else if (check_var_env(env, cmd, s_var))
	{
		exit_stat(0, 0);
		*flag = -1;
		s_var->c = check_value(cmd);
		lstadd_env(&env, s_var->value, s_var->var, s_var);
	}
	free(s_var->value);
	free(s_var->var);
}

void	ft_export_cmd(t_env **data_env, char **cmd, int *flag, t_var *var)
{
	int		i;
	t_env	*env;

	env = *data_env;
	i = 0;
	if (cmd[1])
	{
		while (cmd[++i])
		{
			if (cmd[i] && (check_var(cmd[i]) == -1))
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putendl_fd("': not a valid identifier", 2);
				exit_stat(1, 0);
				*flag = -1;
			}
			else
				ft_expo_env(env, cmd[i], flag, var);
		}
	}
	else
		ft_export(env, flag, var);
}
