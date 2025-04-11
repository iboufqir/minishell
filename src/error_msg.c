/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:06:40 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/20 14:00:14 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_var(t_var *var)
{
	if (var->env != NULL)
		free_list(var->env);
	if (var->ptr != NULL)
		free(var->ptr);
	if (var->str != NULL)
		free(var->str);
	if (var->cwd != NULL)
		free(var->cwd);
	free(var);
}

void	ft_print_msg(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write (2, &msg[i], 1);
		i++;
	}
	return_exit(1, 1);
}

void	msg_error(int num, char *msg, t_var *var)
{
	if (num == -1)
	{
		ft_lstclear(&var->data);
		ft_lstclear_cmd(&var->s_cmd);
		ft_lstclear_env(&var->s_env);
		free_var(var);
		ft_print_msg(msg);
	}
}

void	syntax_msg(char *msg)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\'\n", 2);
}
