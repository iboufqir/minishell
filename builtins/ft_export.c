/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:45:31 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/15 13:44:30 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_value(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '=')
		return (1);
	return (0);
}

int	check_plus(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+')
		i++;
	if (var[i] == '+')
		return (1);
	return (0);
}

int	check_var(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	if (!(var[0] >= 'a' && var[0] <= 'z')
		&& !(var[0] >= 'A' && var[0] <= 'Z') && var[0] != '_')
		return (-1);
	while (var[i] && var[i] != '=' && var[i] != '+')
	{
		if (!(var[i] >= 'a' && var[i] <= 'z')
			&& !(var[i] >= 'A' && var[i] <= 'Z')
			&& !(var[i] >= '0' && var[i] <= '9')
			&& var[i] != '_')
			return (-1);
		i++;
	}
	if (var[i] == '+' && var[i + 1] != '=')
		return (-1);
	return (1);
}

char	*get_var(char *cmd, t_var *s_var)
{
	int		i;
	char	*var;

	var = NULL;
	i = 0;
	if (!cmd)
		return (NULL);
	while (cmd[i] && cmd[i] != '+' && cmd[i] != '=')
		i++;
	var = malloc((i + 1) * sizeof(char));
	if (!var)
		msg_error(-1, "Allocation Failed !!\n", s_var);
	i = 0;
	while (cmd[i] && cmd[i] != '+' && cmd[i] != '=')
	{
		var[i] = cmd[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*get_value(char *cmd, t_var *s_var)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	if (!cmd)
		return (NULL);
	while (cmd[i] && cmd[i] != '=')
		i++;
	if (cmd[i] == '=')
		i++;
	while (cmd[i + j])
		j++;
	value = (char *)malloc((j + 1) * sizeof(char));
	if (!value)
		msg_error(-1, "Allocation Failed !!\n", s_var);
	j = 0;
	while (cmd[i])
		value[j++] = cmd[i++];
	value[j] = '\0';
	return (value);
}
