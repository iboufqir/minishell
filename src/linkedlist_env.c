/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:11:29 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/14 16:27:36 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_envsize(t_env *env)
{
	int		i;
	t_env	*current;

	current = env;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*current;

	if (!lst)
		return ;
	while (*lst)
	{
		current = (*lst)->next;
		free((*lst)->content);
		free((*lst)->variable);
		free(*lst);
		*lst = current;
	}
	free(*lst);
	*lst = NULL;
}

t_env	*lstlast_env(t_env *lst)
{
	t_env	*current;

	current = lst;
	if (!lst)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

void	lstadd_env(t_env **lst, void *content, void *variable, t_var *var)
{
	t_env	*current;
	t_env	*newnode;

	newnode = malloc(sizeof(t_env));
	if (!newnode)
		msg_error(-1, "Allocation Failed !!", var);
	newnode->variable = ft_strdup(variable, var);
	if (var->c)
		newnode->c = '=';
	else
		newnode->c = 'x';
	newnode->content = ft_strdup(content, var);
	newnode->next = NULL;
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = newnode;
		return ;
	}
	current = lstlast_env(*lst);
	current->next = newnode;
}
