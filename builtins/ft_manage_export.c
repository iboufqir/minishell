/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:44:47 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/19 22:59:54 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_manage_export_one(t_env **s_env, t_command *cmd, \
t_var *var, int *flag)
{
	if (dup_redirection(cmd->redirection, cmd->here_fd, var) == -1)
	{
		*flag = -1;
		return ;
	}
	ft_export_cmd(s_env, cmd->cmd, flag, var);
}

void	ft_manage_export(t_env **s_env, t_command *cmd, t_var *var, int *flag)
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
		ft_export_cmd(s_env, cmd->cmd, flag, var);
		exit(0);
	}
	else
	{
		msg_error(close(var->fd[1]), "minishell : close failed\n", var);
		if (cmd->next != NULL)
			msg_error(dup2(var->fd[0], 0), "minishell : dup2 failed\n", var);
		msg_error(close(var->fd[0]), "minishell : close failed\n", var);
	}
}
