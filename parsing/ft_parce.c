/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parce.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboufqir <iboufqir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:17:45 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/24 10:59:10 by iboufqir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_parce_cmd(t_list **current, t_command *new, \
t_var *var, t_env *s_env)
{
	int		i;

	if ((*current)->type == WORD)
	{
		var->ptr_p = ft_expand((*current)->content, var, s_env, 0);
		var->str_p = ft_remove_quotes(var->ptr_p, var);
		var->tmp = ft_remove_backslash(var->str_p, var);
		if (((*current)->prev && !ft_strcmp((*current)->prev->content, \
		"export")) || ft_check(var->ptr_p, '\"') % 2 != 0 \
		|| ft_check(var->ptr_p, '\'') % 2 != 0)
			new->cmd = ft_realloc(new->cmd, var->tmp, ++new->c, var);
		else if (var->tmp && ft_strlen(var->tmp) == 0
			&& (*current)->content[0] != '$')
			new->cmd = ft_realloc(new->cmd, var->tmp, ++new->c, var);
		else
		{
			i = 0;
			var->ptr_ex = ft_split(var->tmp, ' ', var);
			while (var->ptr_ex && var->ptr_ex[i])
				new->cmd = ft_realloc(new->cmd, \
				var->ptr_ex[i++], ++new->c, var);
			free_list(var->ptr_ex);
		}
		(free(var->ptr_p), free(var->str_p), free(var->tmp));
	}
}

static void	ft_parce_redirection(t_list **current, t_command *new, t_var *var, \
t_env *s_env)
{
	if ((*current)->type == REDIR_IN || (*current)->type == REDIR_OUT \
	|| (*current)->type == DREDIR_OUT)
	{
		new->redirection = ft_realloc(new->redirection, \
		(*current)->content, ++new->r, var);
		if ((*current)->next)
		{
			(*current) = (*current)->next;
			var->ptr_p = ft_expand((*current)->content, var, s_env, 0);
			var->str_p = ft_remove_quotes(var->ptr_p, var);
			if (ft_manage_ambiguous(var->str_p, var->ptr_p, var) == -1)
				var->ambiguous = 1;
			new->redirection = ft_realloc(new->redirection, \
			var->str_p, ++new->r, var);
		}
		(free(var->ptr_p), free(var->str_p));
	}
}

static void	ft_parce_heredoc(t_list **current, t_command *new, t_var *var)
{
	if ((*current)->type == HERE_DOC)
	{
		new->redirection = ft_realloc(new->redirection, \
		(*current)->content, ++new->r, var);
		if ((*current)->type == HERE_DOC)
			new->here_fd = (*current)->fd;
		if ((*current)->next)
		{
			(*current) = (*current)->next;
			new->redirection = ft_realloc(new->redirection, \
			(*current)->content, ++new->r, var);
		}
	}
}

static void	while_(t_list **data, t_command **data_cmd, \
t_var *var, t_env *s_env)
{
	t_command	*new;
	t_list		*current;

	new = ft_malloc(var);
	current = *data;
	var->ambiguous = 0;
	if (!current)
		free(new);
	while (current)
	{
		ft_parce_cmd(&current, new, var, s_env);
		ft_parce_redirection(&current, new, var, s_env);
		ft_parce_heredoc(&current, new, var);
		if (!current->next || current->type == PIPE_LINE)
		{
			ft_lstadd_back_cmd(data_cmd, new);
			if (current->type == PIPE_LINE)
				new = ft_malloc(var);
			else
				break ;
		}
		current = current->next;
	}
}

void	parsing(t_list **data, t_command **data_cmd, t_var *var, t_env *s_env)
{
	if (ft_syntax_error(*data, var, s_env) == 1)
	{
		exit_stat(258, 0);
		return ;
	}
	while_(data, data_cmd, var, s_env);
}
