/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 08:51:56 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/19 22:18:27 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_manage_ambiguous(char *str, char *ptr_, t_var *var)
{
	char	**ptr;
	int		i;

	ptr = ft_split(str, ' ', var);
	i = 0;
	while (ptr[i])
		i++;
	free_list(ptr);
	if (i != 1 && (ft_check(ptr_, '\"') % 2 == 0 \
	|| ft_check(ptr_, '\'') % 2 != 0))
		return (-1);
	return (0);
}

int	ft_dup_outfile(char *redirection, char *file, t_var *var)
{
	if (ft_strcmp(redirection, ">>") == 0 && var->ambiguous != 1)
		var->outfile = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (ft_strcmp(redirection, ">") == 0 && var->ambiguous != 1)
		var->outfile = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (var->outfile == -1 || var->ambiguous == 1)
	{
		if (errno == 13)
			ft_putendl_fd("minishell : Permission denied", 2);
		else if (var->ambiguous == 1)
			ft_putendl_fd("minishell: ambiguous redirect", 2);
		else
			ft_putendl_fd("minishell : No such file or directory", 2);
		exit_stat(1, 0);
		return (-1);
	}
	msg_error(dup2(var->outfile, 1), "minishell : dup2 failed\n", var);
	msg_error(close(var->outfile), "minishell : close failed\n", var);
	var->flag = 1;
	return (0);
}

int	ft_dup_infile(char *file, t_var *var)
{
	var->infile = open(file, O_RDONLY, 0644);
	if (var->infile == -1)
	{
		var->in_failed = -1;
		ft_putendl_fd("minishell : No such file or directory", 2);
		exit_stat(1, 0);
		return (-1);
	}
	msg_error(dup2(var->infile, 0), "minishell : dup2 failed\n", var);
	msg_error(close(var->infile), "minishell : close failed\n", var);
	return (0);
}

int	dup_redirection(char **redirection, int here_fd, t_var *var)
{
	(1) && (var->i = 0, var->in_failed = 0, var->flag = 0);
	while (redirection && redirection[var->i])
	{
		if (ft_strcmp(redirection[var->i], "<<") == 0 && here_fd != -1)
			msg_error(dup2(here_fd, 0), "minishell : dup2 failed\n", var);
		else if (ft_strcmp(redirection[var->i], "<") == 0)
		{
			if (ft_dup_infile(redirection[++var->i], var) == -1)
				return (-1);
		}
		else if (var->in_failed != -1 && \
		(ft_strcmp(redirection[var->i], ">>") == 0
				|| ft_strcmp(redirection[var->i], ">") == 0))
		{
			if (ft_dup_outfile(redirection[var->i], \
			redirection[++var->i], var) == -1)
				return (-1);
		}
		var->i++;
	}
	if (here_fd != 0)
		msg_error(close(here_fd), "minishell : close failed\n", var);
	return (0);
}
