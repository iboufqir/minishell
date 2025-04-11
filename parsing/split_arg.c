/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:37:19 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/16 23:41:22 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_init(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (2);
		else if (str[i] == '<')
			return (3);
		else if (str[i] == '>')
			return (4);
		else
			return (1);
		i++;
	}
	return (0);
}

void	list_init(char **cmd, t_list **data, t_var *var)
{
	int		i;
	int		token;
	t_list	*new;

	i = 0;
	while (cmd && cmd[i])
	{
		token = token_init(cmd[i]);
		new = lstnew(cmd[i], token, var);
		ft_lstadd_back(data, new);
		i++;
	}
}

void	split_arg(t_list **data, t_command **data_cmd, t_var *var, t_env *s_env)
{
	char	**cmd;

	cmd = ft_split_custom(var->line, var);
	if (!cmd)
		msg_error(-1, "Error Split\n", var);
	list_init(cmd, data, var);
	free_list(cmd);
	parsing(data, data_cmd, var, s_env);
}
