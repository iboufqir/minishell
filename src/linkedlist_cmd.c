/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:11:29 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/11 17:54:33 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*ft_lstlast_cmd(t_command *lst)
{
	t_command	*current;

	current = lst;
	if (!lst)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

void	ft_lstclear_cmd(t_command **lst)
{
	t_command	*current;

	if (!lst)
		return ;
	while (*lst)
	{
		current = (*lst)->next;
		free_list((*lst)->cmd);
		free_list((*lst)->redirection);
		free(*lst);
		*lst = current;
	}
	free(*lst);
	*lst = NULL;
}

void	ft_lstadd_back_cmd(t_command **lst, t_command *new)
{
	t_command	*current;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = ft_lstlast_cmd(*lst);
	current->next = new;
}
