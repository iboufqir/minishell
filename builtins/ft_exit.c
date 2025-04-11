/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboufqir <iboufqir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:38:46 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/24 10:54:53 by iboufqir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_atoi_exit(char *str)
{
	int			i;
	int			n;
	long long	r;

	i = 0;
	r = 0;
	n = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		r = r * 10 + (str[i++] - 48);
		if (r < 0)
			return (-2);
	}
	return (r * n);
}

int	ft_exit_args(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!cmd || !cmd[1])
		return (0);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][0] == '-' || cmd[i][0] == '+')
				;
			else if (!ft_isdigit(cmd[1][j]) || ft_atoi_exit(cmd[1]) == -2)
				return (-1);
			else if (!ft_isdigit(cmd[i][j]))
				return (-2);
			j++;
		}
		i++;
	}
	if (i != 2)
		return (-2);
	return (i);
}

void	ft_exit(char **cmd, t_var *var, int *flag)
{
	if (!var->exit_flag)
		ft_putstr_fd("exit\n", 2);
	if (ft_exit_args(cmd) == -2)
	{
		exit_stat(1, 0);
		ft_putstr_fd("minishell : exit: too many arguments\n", 2);
		*flag = -1;
	}
	else if (ft_exit_args(cmd) == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		return_exit(255, 0);
	}
	else if (ft_exit_args(cmd) == 0 && var)
		return_exit(1, 1);
	else
		return_exit(ft_atoi(cmd[1]), 0);
}

void	ft_manage_exit_one(t_command *cmd, t_var *var, int *flag)
{
	if (dup_redirection(cmd->redirection, cmd->here_fd, var) == -1)
	{
		*flag = -1;
		return ;
	}
	ft_exit(cmd->cmd, var, flag);
}

void	ft_manage_exit(t_command *cmd, t_var *var, int *flag)
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
		ft_exit(cmd->cmd, var, flag);
	}
	else
	{
		msg_error(close(var->fd[1]), "minishell : close failed\n", var);
		if (cmd->next != NULL)
			msg_error(dup2(var->fd[0], 0), "minishell : dup2 failed\n", var);
		msg_error(close(var->fd[0]), "minishell : close failed\n", var);
	}
}
