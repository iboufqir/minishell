/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboufqir <iboufqir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:42:52 by iboufqir          #+#    #+#             */
/*   Updated: 2024/07/24 10:47:21 by iboufqir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	int	pid;

	(void)sig;
	pid = wait(NULL);
	if (pid <= 0)
	{
		exit_stat(1, 0);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		exit_stat(130, 0);
		g_sig_catch = 1;
		printf("\n");
	}
}

void	handle_sigquit(int sig)
{
	(void)sig;
	if (waitpid(-1, 0, WNOHANG) == 0)
	{
		exit_stat(131, 0);
		g_sig_catch = 1;
		printf("Quit: 3\n");
	}
}

void	signal_handlers(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_sigint_herdoc(int sig)
{
	int	pid;

	(void)sig;
	if (sig == SIGINT)
	{
		pid = wait(NULL);
		if (pid <= 0)
			return_exit(0, 0);
		else
		{
			exit_stat(1, 0);
			g_sig_catch = 1;
			printf("\n");
		}
	}
}

void	signal_handlers_herdoc(void)
{
	struct sigaction	sa;

	rl_catch_signals = 1;
	sa.sa_handler = handle_sigint_herdoc;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
