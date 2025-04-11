/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboufqir <iboufqir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:51:42 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/24 10:49:45 by iboufqir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_unset(t_env *tmp)
{
	free(tmp->content);
	free(tmp->variable);
	free(tmp);
}

int	valid_arg(char *cmd, int *flag)
{
	if (cmd && check_var(cmd) == -1)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		exit_stat(1, 0);
		*flag = -1;
		return (1);
	}
	return (0);
}

void	ft_unset(t_env **s_env, char **cmd, int *flag)
{
	t_env	*current;
	t_env	*tmp;
	int		i;

	i = 0;
	while (cmd && cmd[++i])
	{
		current = *s_env;
		while (current && current->next && !valid_arg(cmd[i], flag))
		{
			if (ft_strcmp(current->next->variable, cmd[i]) == 0)
			{
				tmp = current->next;
				current->next = current->next->next;
				free_unset(tmp);
			}
			current = current->next;
		}
		if (*s_env && ft_strcmp((*s_env)->variable, cmd[i]) == 0)
		{
			tmp = *s_env;
			*s_env = (*s_env)->next;
			free_unset(tmp);
		}
	}
}

void	ft_manage_unset_one(t_env **s_env, t_command *cmd, \
t_var *var, int *flag)
{
	if (dup_redirection(cmd->redirection, cmd->here_fd, var) == -1)
	{
		*flag = -1;
		return ;
	}
	ft_unset(s_env, cmd->cmd, flag);
	free_list(var->env);
	var->env = ft_duplicat_env(*s_env, var);
	if (*flag != -1)
	{
		exit_stat(0, 0);
		*flag = -1;
	}
}

void	ft_manage_unset(t_env **s_env, t_command *cmd, t_var *var, int *flag)
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
		ft_unset(s_env, cmd->cmd, flag);
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
