/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:37:39 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/17 10:57:56 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_heredoc_expand(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	ft_child_here(t_heredoc *here, t_var *var, t_env *s_env)
{
	while (1)
	{
		here->line = readline("> ");
		if (!here->line)
			break ;
		if (ft_strcmp(here->line, here->new_eof) == 0)
			break ;
		if (here->expand_stat == 0)
			here->ptr = ft_expand(here->line, var, s_env, 1);
		else
			here->ptr = ft_strdup(here->line, var);
		here->tmp = ft_remove_backslash(here->ptr, var);
		ft_putendl_fd(here->tmp, here->fd[0]);
		(free(here->line), free(here->ptr), free(here->tmp));
	}
	if (here->line)
		free(here->line);
	exit(0);
}

int	ft_here_doc(char *eof, t_var *var, t_env *s_env)
{
	t_heredoc	here;
	int			status;

	unlink("/tmp/here_doc");
	here.fd[0] = open("/tmp/here_doc", O_CREAT | O_WRONLY | O_APPEND, 0644);
	here.fd[1] = open("/tmp/here_doc", O_RDONLY, 0644);
	unlink("/tmp/here_doc");
	here.expand_stat = ft_heredoc_expand(eof);
	here.new_eof = ft_remove_here(eof, var);
	signal_handlers_herdoc();
	here.pid = fork();
	msg_error(here.pid, "minishell : fork failed\n", var);
	if (here.pid == 0)
		ft_child_here(&here, var, s_env);
	else
	{
		waitpid(here.pid, &status, 0);
		exit_stat(WEXITSTATUS(status), 0);
		free(here.new_eof);
		msg_error(close(here.fd[0]), "minishell : close failed\n", var);
		if (g_sig_catch != 0)
			msg_error(close(here.fd[1]), "minishell : close failed\n", var);
	}
	signal_handlers();
	return (here.fd[1]);
}
