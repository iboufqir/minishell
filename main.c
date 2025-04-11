/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahomari <ahomari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:19:06 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/24 12:19:07 by ahomari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	while_true(t_list **data, t_command **s_cmd, t_env **s_env, t_var *var)
{
	while (1)
	{
		msg_error(tcgetattr(0, &var->termios_p), "tcgetattr\n", var);
		g_sig_catch = 0;
		signal_handlers();
		var->line = readline("➜ MyMinishell-01$ ");
		if (!var->line)
			msg_error(-1, "exit\n", var);
		if (var->line[0])
			add_history(var->line);
		split_arg(data, s_cmd, var, *s_env);
		msg_error(var->std_fd[0] = dup(0), "minishell : dup failed\n", var);
		msg_error(var->std_fd[1] = dup(1), "minishell : dup failed\n", var);
		ft_manage_execution(var, s_env, *s_cmd);
		msg_error(dup2(var->std_fd[0], 0), "minishell : dup2 failed\n", var);
		msg_error(dup2(var->std_fd[1], 1), "minishell : dup2 failed\n", var);
		msg_error(close(var->std_fd[0]), "minishell : close failed\n", var);
		msg_error(close(var->std_fd[1]), "minishell : close failed\n", var);
		while (waitpid(-1, NULL, 0) > 0)
			;
		ft_lstclear(data);
		ft_lstclear_cmd(s_cmd);
		free(var->line);
		msg_error(tcsetattr(0, TCSANOW, &var->termios_p), "tcsetattr\n", var);
	}
}

int	main(int ac, char **av, char **env)
{
	t_list		*data;
	t_command	*s_cmd;
	t_env		*s_env;
	t_var		*var;

	(void)ac;
	(void)av;
	(1) && (data = NULL, s_cmd = NULL, s_env = NULL);
	var = malloc(sizeof(t_var));
	if (!var)
		msg_error(-1, "Allocation Failed\n", var);
	ft_memset(var, 0, sizeof(t_var));
	var->cwd = getcwd(NULL, 0);
	if (env[0] == NULL)
	{
		var->empty = 1;
		ft_empty_env(&s_env, var);
		var->env = ft_duplicat_env(s_env, var);
	}
	else
	{
		ft_manage_env(env, &s_env, var);
		var->env = ft_duplicat_env(s_env, var);
	}
	while_true(&data, &s_cmd, &s_env, var);
}
