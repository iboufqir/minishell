/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboufqir <iboufqir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:48:53 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/24 10:18:07 by iboufqir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_get_cmd(char **path, char *cmd, t_var *var)
{
	char	*tmp;
	char	*ptr;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/", var);
		ptr = ft_strjoin(tmp, cmd, var);
		free(tmp);
		if (access(ptr, X_OK) == 0)
			return (ptr);
		free(ptr);
		i++;
	}
	return (NULL);
}

void	get_execve(char **av, char **env, t_var *var)
{
	int		find_path;
	char	**cmd_path;
	char	*cmd;

	if (ft_strchr(av[0], '/') != NULL)
	{
		if (execve(av[0], av, env) == -1)
			exec_failed(av[0]);
	}
	find_path = ft_index(env);
	if (find_path == -2)
	{
		ft_putendl_fd("minishell : No such file or directory", 2);
		exit(127);
	}
	cmd_path = ft_split(env[find_path] + 5, ':', var);
	cmd = ft_get_cmd(cmd_path, av[0], var);
	if (execve(cmd, av, env) == -1)
		exec_failed(av[0]);
}

void	ft_execution_cmd(t_command *cmd, t_var *var)
{
	msg_error(pipe(var->fd), "minishell : pipe failed\n", var);
	cmd->pid = fork();
	msg_error(cmd->pid, "minishell : fork failed\n", var);
	if (cmd->pid == 0)
	{
		if (dup_redirection(cmd->redirection, cmd->here_fd, var) == -1)
			exit(1);
		msg_error(close(var->fd[0]), "minishell : close failed\n", var);
		if (var->flag != 1 && cmd->next != NULL)
			msg_error(dup2(var->fd[1], 1), "minishell : dup2 failed\n", var);
		msg_error(close(var->fd[1]), "minishell : close failed\n", var);
		get_execve(cmd->cmd, var->env, var);
	}
	else
	{
		msg_error(close(var->fd[1]), "minishell : close failed\n", var);
		if (cmd->next != NULL)
			msg_error(dup2(var->fd[0], 0), "minishell : dup2 failed\n", var);
		msg_error(close(var->fd[0]), "minishell : close failed\n", var);
	}
}

void	ft_manage_execution(t_var *var, t_env **s_env, t_command *cmd)
{
	t_command	*current;
	int			flag;

	current = cmd;
	while (current && g_sig_catch == 0)
	{
		if (current && current->cmd == NULL)
			dup_redirection(current->redirection, current->here_fd, var);
		else if (cmd && !cmd->next)
		{
			change_value_env(s_env, cmd->cmd, 0, var);
			manage_one_cmd(var, s_env, current);
		}
		else if (cmd && cmd->next)
		{
			var->exit_flag = 1;
			change_value_env(s_env, cmd->cmd, 1, var);
			manage_multi_cmd(var, s_env, current);
		}
		flag = current->flag;
		if (current->here_fd != 0)
			close(current->here_fd);
		current = current->next;
	}
	wait_exit(cmd, flag);
}
