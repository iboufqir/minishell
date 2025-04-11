/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:29:37 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/20 11:58:47 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_duplicat_env(t_env *s_env, t_var *var)
{
	int		i;
	char	**ptr;
	char	*tmp;
	t_env	*current;

	ptr = malloc((ft_envsize(s_env) + 1) * sizeof(char *));
	if (!ptr)
		msg_error(-1, "Allocation Failed !!\n", var);
	current = s_env;
	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->variable, "=", var);
		ptr[i] = ft_strjoin(tmp, current->content, var);
		free(tmp);
		i++;
		current = current->next;
	}
	ptr[i] = 0;
	return (ptr);
}

void	ft_manage_env(char **env, t_env **s_env, t_var *var)
{
	int		i;
	char	*content;
	char	*variable;

	i = 0;
	while (env[i])
	{
		content = ft_strdup(ft_strchr(env[i], '='), var);
		variable = ft_substr(env[i], 0, ft_strlen(env[i]) - \
		ft_strlen(content), var);
		var->c = 1;
		lstadd_env(s_env, content + 1, variable, var);
		free(content);
		free(variable);
		i++;
	}
}

void	printlist_env(t_env *data, t_var *var)
{
	t_env	*current;

	current = data;
	while (current)
	{
		if (current->c == '=')
		{
			if (var->empty && ft_strcmp(current->variable, "PATH") != 0)
				printf("%s=%s\n", current->variable, current->content);
			else if (!var->empty)
				printf("%s=%s\n", current->variable, current->content);
		}
		current = current->next;
	}
}

void	ft_manage_print_env(t_command *cmd, t_var *var, t_env *s_env)
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
		printlist_env(s_env, var);
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
