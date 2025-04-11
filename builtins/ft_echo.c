/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:26:48 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/20 23:58:07 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_caracter(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != c)
			return (-1);
		i++;
	}
	return (i);
}

void	ft_echo(char **cmd)
{
	int	start;
	int	check;
	int	all_n;

	start = 1;
	check = 0;
	while (cmd && cmd[start])
	{
		if (cmd && ft_strncmp(cmd[1], "-n", 2) == 0 && check == 0)
		{
			all_n = ft_check_caracter(cmd[start] + 2, 'n');
			if (all_n != -1)
			{
				start = 2;
				check = 1;
			}
		}
		ft_putstr_fd(cmd[start], 1);
		if (cmd[start] != 0)
			ft_putchar_fd(' ', 1);
		start++;
	}
	if (check == 0)
		ft_putchar_fd('\n', 1);
}

void	ft_manage_echo(t_command *cmd, t_var *var)
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
		ft_echo(cmd->cmd);
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
