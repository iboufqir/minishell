/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:24:57 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/11 14:34:37 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes(char *str)
{
	int		i;
	char	check_quotes;

	i = 0;
	check_quotes = 0;
	while (str[i])
	{
		if (check_quotes == '\0' && (str[i] == '\"' || str[i] == '\''))
			check_quotes = str[i];
		else if (check_quotes == str[i])
			check_quotes = 0;
		i++;
	}
	if (check_quotes == '\"' || check_quotes == '\'')
	{
		syntax_msg("\' or \"");
		return (1);
	}
	return (0);
}

void	ft_close_fd(t_list *data)
{
	t_list	*current;

	current = data;
	while (current)
	{
		if (current->type == HERE_DOC && current->fd != -1)
		{
			close(current->fd);
			current->fd = -1;
		}
		current = current->next;
	}
}

int	syntax_error(t_list *data, t_var *var, t_env *s_env)
{
	t_list	*current;

	current = data;
	while (current)
	{
		if (check_quotes(current->content) == 1)
			return (1);
		if ((current->type >= PIPE_LINE && !current->next)
			|| (current->type > PIPE_LINE && current->next->type >= PIPE_LINE)
			|| (current->type == PIPE_LINE && current->next->type == PIPE_LINE))
		{
			if (current->type >= PIPE_LINE && !current->next)
				syntax_msg("newline");
			else
				syntax_msg(current->next->content);
			return (1);
		}
		if (current->type == HERE_DOC && !g_sig_catch)
		{
			ft_close_fd(data);
			current->fd = ft_here_doc(current->next->content, var, s_env);
		}
		current = current->next;
	}
	return (0);
}

int	ft_syntax_error(t_list *data, t_var *var, t_env *s_env)
{
	if (data && data->type == PIPE_LINE)
	{
		syntax_msg("|");
		return (1);
	}
	if (syntax_error(data, var, s_env) == 1)
		return (1);
	return (0);
}
