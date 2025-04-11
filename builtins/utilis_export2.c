/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_export2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:25:57 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/15 15:27:25 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_export(char *variable, char *content, char c)
{
	printf("declare -x %s", variable);
	if (c == '=')
	{
		printf("%c", c);
		printf("\"%s\"\n", content);
	}
	else
		printf("\n");
}
