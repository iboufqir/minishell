/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:33:35 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/19 21:44:43 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_env *s_env, t_var *var)
{
	t_env	*current;
	int		flag;

	flag = 0;
	current = s_env;
	while (current)
	{
		if (ft_strcmp(current->variable, "PWD") == 0)
		{
			flag = 1;
			ft_putendl_fd(current->content, 1);
		}
		current = current->next;
	}
	if (!flag)
	{
		ft_putendl_fd(var->cwd, 1);
	}
}

void	ft_manage_pwd(t_env *s_env, t_command *cmd, t_var *var)
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
		ft_pwd(s_env, var);
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
