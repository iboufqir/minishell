/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:11:29 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/15 13:57:42 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (!lst)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current;

	current = lst;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*current;

	if (!lst)
		return ;
	while (*lst)
	{
		current = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = current;
	}
	free(*lst);
	*lst = NULL;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = ft_lstlast(*lst);
	current->next = new;
	new->prev = current;
}

t_list	*lstnew(void *content, int token, t_var *var)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		msg_error(-1, "Allocation Failed\n", var);
	newnode->content = ft_strdup(content, var);
	newnode->len = ft_strlen(content);
	newnode->fd = -1;
	if (token == 3 && ft_strlen(content) != 1)
		newnode->type = 5;
	else if (token == 4 && ft_strlen(content) != 1)
		newnode->type = 6;
	else
		newnode->type = token;
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
}
