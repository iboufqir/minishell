/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:21:36 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/19 21:43:32 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd1(t_env **data_env, char *cmd, int *flag, t_var *var)
{
	char		*newpwd;

	if (chdir(cmd) == -1)
	{
		exit_stat(1, 0);
		*flag = -1;
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return ;
	}
	newpwd = getcwd(NULL, 1024);
	change_pwd(data_env, "PWD", newpwd, var);
	if (newpwd)
	{
		free(var->cwd);
		var->cwd = ft_strdup(newpwd, var);
		if (!var->cwd)
			msg_error(-1, "Allocation Failed !!", var);
	}
	exit_stat(0, 0);
	*flag = -1;
	free(newpwd);
}

void	ft_cd(t_env **data_env, char *cmd, int *flag, t_var *var)
{
	char		*oldpwd;
	static int	flg;

	flg = 0;
	oldpwd = getcwd(NULL, 1024);
	if (!oldpwd)
	{
		if (!flg)
		{
			exit_stat(1, 0);
			flg = 1;
			*flag = -1;
		}
		else
		{
			exit_stat(0, 0);
			*flag = -1;
		}
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	change_pwd(data_env, "OLDPWD", oldpwd, var);
	free(oldpwd);
	ft_cd1(data_env, cmd, flag, var);
}

void	manage_cd(t_env **data_env, char *cmd, int *flag, t_var *var)
{
	if (cmd == NULL)
	{
		cmd = ft_getenv(data_env, "HOME");
		if (!cmd)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			exit_stat(1, 0);
			*flag = -1;
			return ;
		}
		exit_stat(0, 0);
		*flag = -1;
	}
	ft_cd(data_env, cmd, flag, var);
}

void	ft_manage_cd_one(t_command *cmd, t_var *var, t_env **s_env, int *flag)
{
	if (dup_redirection(cmd->redirection, cmd->here_fd, var) == -1)
	{
		*flag = -1;
		return ;
	}
	manage_cd(s_env, cmd->cmd[1], flag, var);
}

void	ft_manage_cd(t_command *cmd, t_var *var, t_env **s_env, int *flag)
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
		manage_cd(s_env, cmd->cmd[1], flag, var);
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
