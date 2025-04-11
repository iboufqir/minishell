/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:04:39 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/20 23:38:33 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_failed(char *cmd)
{
	int	n;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	n = errno;
	if (n == 13 && (cmd && cmd[0]))
	{
		ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
	else
	{
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
}

void	wait_exit(t_command *cmd, int flag)
{
	t_command	*current;
	int			status;

	if ((cmd && cmd->cmd && flag != -1))
	{
		current = ft_lstlast_cmd(cmd);
		waitpid(current->pid, &status, 0);
		exit_stat(WEXITSTATUS(status), 0);
		g_sig_catch = 1;
	}
}

int	ft_index(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (i);
		i++;
	}
	return (-2);
}

void	manage_multi_cmd(t_var *var, t_env **s_env, t_command *current)
{
	if (current->cmd && ft_strcmp(current->cmd[0], "cd" ) == 0)
		ft_manage_cd(current, var, s_env, &current->flag);
	else if (current->cmd && ft_strcmp(current->cmd[0], "echo") == 0)
		ft_manage_echo(current, var);
	else if (current->cmd && (ft_strcmp(current->cmd[0], "pwd") == 0 \
	|| ft_strcmp(current->cmd[0], "PWD") == 0))
		ft_manage_pwd(*s_env, current, var);
	else if (current->cmd && ft_strcmp(current->cmd[0], "export") == 0)
		ft_manage_export(s_env, current, var, &current->flag);
	else if (current->cmd && ft_strcmp(current->cmd[0], "exit") == 0)
		ft_manage_exit(current, var, &current->flag);
	else if (current->cmd && ft_strcmp(current->cmd[0], "unset") == 0)
		ft_manage_unset(s_env, current, var, &current->flag);
	else if (current->cmd && ft_index(var->env) != -2 && !current->cmd[1] \
	&& (ft_strcmp(current->cmd[0], "env") == 0 || \
	ft_strcmp(current->cmd[0], "ENV") == 0))
		ft_manage_print_env(current, var, *s_env);
	else if (current->cmd)
		ft_execution_cmd(current, var);
}

void	manage_one_cmd(t_var *var, t_env **s_env, t_command *current)
{
	if (current->cmd && ft_strcmp(current->cmd[0], "cd" ) == 0)
		ft_manage_cd_one(current, var, s_env, &current->flag);
	else if (current->cmd && ft_strcmp(current->cmd[0], "echo") == 0)
		ft_manage_echo(current, var);
	else if (current->cmd && (ft_strcmp(current->cmd[0], "pwd") == 0 \
	|| ft_strcmp(current->cmd[0], "PWD") == 0))
		ft_manage_pwd(*s_env, current, var);
	else if (current->cmd && ft_strcmp(current->cmd[0], "export") == 0)
	{
		ft_manage_export_one(s_env, current, var, &current->flag);
		free_list(var->env);
		var->env = ft_duplicat_env(*s_env, var);
	}
	else if (current->cmd && ft_strcmp(current->cmd[0], "exit") == 0)
		ft_manage_exit_one(current, var, &current->flag);
	else if (current->cmd && ft_strcmp(current->cmd[0], "unset") == 0)
		ft_manage_unset_one(s_env, current, var, &current->flag);
	else if (current->cmd && ft_index(var->env) != -2 && !current->cmd[1] \
	&& (ft_strcmp(current->cmd[0], "env") == 0 || \
	ft_strcmp(current->cmd[0], "ENV") == 0))
		ft_manage_print_env(current, var, *s_env);
	else if (current->cmd)
		ft_execution_cmd(current, var);
}
