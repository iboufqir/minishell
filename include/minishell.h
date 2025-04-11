/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboufqir <iboufqir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:39:21 by ahomari           #+#    #+#             */
/*   Updated: 2024/07/24 11:02:22 by iboufqir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>

int	g_sig_catch;
// static int n = 0;
// # define malloc(size) (n++ == 22 ? NULL : malloc(size))

typedef enum e_token
{
	WORD = 1,
	PIPE_LINE = 2,
	REDIR_IN = 3,
	REDIR_OUT = 4,
	HERE_DOC = 5,
	DREDIR_OUT = 6,
}	t_token;

typedef struct s_command
{
	int					c;
	int					r;
	int					flag;
	pid_t				pid;
	char				**cmd;
	char				**redirection;
	int					here_fd;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char			*variable;
	char			c;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_heredoc
{
	int		fd[2];
	int		pid;
	int		expand_stat;
	char	*line;
	char	*ptr;
	char	*tmp;
	char	*new_eof;
}				t_heredoc;

typedef struct s_list
{
	char			*content;
	int				len;
	int				fd;
	enum e_token	type;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_var
{
	int				i;
	int				start;
	size_t			end;
	int				j;
	int				c;
	int				exit_flag;
	int				empty;
	int				flag;
	int				in_failed;
	int				infile;
	int				outfile;
	int				fd[2];
	int				std_fd[2];
	char			single;
	int				ambiguous;
	char			**env;
	char			**ptr_ex;
	char			*ptr;
	char			*ptr_p;
	char			*var;
	char			*value;
	char			*str;
	char			*str_p;
	char			*tmp;
	char			*line;
	char			*cwd;
	t_command		*s_cmd;
	t_env			*s_env;
	t_list			*data;
	struct termios	termios_p;
}	t_var;

t_command	*ft_malloc(t_var *var);
int			ft_check(char *str, char c);
int			ft_manage_ambiguous(char *str, char *ptr_, t_var *var);
t_list		*lstnew(void *content, int token, t_var *var);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstclear(t_list **lst);	
int			ft_lstsize(t_list *lst);
void		*free_list(char **strs);
void		ft_lstclear_cmd(t_command **lst);
t_command	*ft_lstlast_cmd(t_command *lst);
void		ft_lstadd_back_cmd(t_command **lst, t_command *new);
void		ft_manage_execution(t_var *var, t_env **s_env, t_command *cmd);
void		msg_error(int num, char *msg, t_var *var);
void		get_execve(char **av, char **env, t_var *var);
char		*ft_get_cmd(char **path, char *cmd, t_var *var);
int			ft_index(char **env);
void		syntax_msg(char *msg);
void		ft_manage_env(char **env, t_env **s_env, t_var *var);
void		lstadd_env(t_env **lst, void *content, void *variable, t_var *var);
void		printlist_env(t_env *data, t_var *var);
char		*add_space(char *str, t_var *var);
void		ft_manage_echo(t_command *cmd, t_var *var);
void		ft_manage_pwd(t_env *s_env, t_command *cmd, t_var *var);
void		ft_manage_unset_one(t_env **s_env, \
			t_command	*cmd, t_var *var, int *flag);
void		ft_manage_unset(t_env **s_env, \
t_command *cmd, t_var *var, int *flag);
void		split_arg(t_list **data, t_command	**data_cmd, t_var *var, \
			t_env *s_env);
void		ft_manage_exit_one(t_command *cmd, t_var *var, int *flag);
void		list_init(char **cmd, t_list **data, t_var *var);
int			ft_syntax_error(t_list *data, t_var *var, t_env *s_env);
char		*ft_remove_quotes(char *str, t_var *var);
char		**ft_realloc(char **ptr, char *str, size_t new_size, t_var *var);
char		**ft_split_custom(char *s, t_var *var);
char		*ft_expand(char *str, t_var *var, t_env *s_env, int flag);
int			ft_here_doc(char *eof, t_var *var, t_env *s_env);
void		*free_list(char **strs);
int			dup_redirection(char **redirection, int here_fd, t_var *var);
void		ft_manage_export(t_env **s_env, t_command *cmd, \
			t_var *var, int *flag);
char		**ft_duplicat_env(t_env *s_env, t_var *var);
void		ft_manage_print_env(t_command *cmd, t_var *var, t_env *s_env);
void		ft_export(t_env *env, int *flag, t_var *var);
void		ft_manage_exit(t_command *cmd, t_var *var, int *flag);
void		signal_handlers(void);
void		signal_handlers_herdoc(void);
char		*ft_remove_here(char *str, t_var *var);
void		return_exit(int oldexit, int n);
int			exit_stat(int oldexit, int n);
void		wait_exit(t_command *cmd, int flag);
void		ft_manage_cd(t_command *cmd, t_var *var, t_env **s_env, int *flag);
void		ft_manage_cd_one(t_command *cmd, t_var *var, \
			t_env **s_env, int *flag);
void		manage_multi_cmd(t_var *var, t_env **s_env, t_command *current);
void		manage_one_cmd(t_var *var, t_env **s_env, t_command *current);
void		ft_execution_cmd(t_command *cmd, t_var *var);
void		ft_exit(char **cmd, t_var *var, int *flag);
void		ft_manage_export_one(t_env **s_env, \
			t_command *cmd, t_var *var, int *flag);
void		ft_lstclear_env(t_env **lst);
int			count_sub(char *str);
void		parsing(t_list **data, t_command **data_cmd, t_var *var, \
			t_env *s_env);
void		ft_expo_env(t_env *env, char *cmd, int *flag, t_var *s_var);
void		ft_export_cmd(t_env **data_env, char **cmd, int *flag, t_var *var);
int			check_value(char *var);
int			check_plus(char *var);
int			check_var(char *var);
char		*get_var(char *cmd, t_var *s_var);
char		*get_value(char *cmd, t_var *s_var);
void		exec_failed(char *cmd);
void		change_pwd(t_env **data_env, char *pwd, char *c, t_var *var);
char		*ft_getenv(t_env **data_env, char *str);
char		*ft_remove_backslash(char *str, t_var *var);
void		change_value_env(t_env **env, char **cmd, int flag, t_var *var);
void		ft_empty_env(t_env **s_env, t_var *var);
void		ft_print_export(char *variable, char *content, char c);
int			ft_atoi(const char *str);
char		*ft_itoa(int n, t_var *var);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strdup(char *s1, t_var *var);
char		*ft_substr(char *s, unsigned int start, size_t len, t_var *var);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
char		*ft_strjoin(char *s1, char *s2, t_var *var);
int			ft_isalpha(int c);
void		*ft_memcpy(void *dst, void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strchr(char *s, int c);
size_t		ft_strlen(char *s);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_strcmp(char *s1, char *s2);
char		**ft_split(char *s, char c, t_var *var);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_envsize(t_env *env);
int			is_space(char c);
int			count_s(char *str);
char		*value_(char *str, t_var *var);
#endif