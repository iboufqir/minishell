/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:45:34 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/17 10:30:18 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_stat(int oldexit, int n)
{
	static int	flg;

	if (n == 0 && g_sig_catch == 0)
		flg = oldexit;
	return (flg);
}

void	return_exit(int oldexit, int n)
{
	int	v_exit;

	v_exit = exit_stat(oldexit, n);
	exit(v_exit);
}
