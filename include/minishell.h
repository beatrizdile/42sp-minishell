/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:21:13 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/11/01 10:21:14 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>

/* Characteres */
# define METACHAR "<>| "
# define VAR_BLOCK " <>|?\'\"/$"
# define BLANK "\t\n\v\f\r "
# define S_QUOTE '\''
# define D_QUOTES '\"'

/* Error defines */
# define SUCCESS 0
# define FAILURE 1
# define ERRBUILTIN 2
# define ERRCMD_NOTEXEC 126
# define ERRCMD_NOTFOUNT 127
# define ERR_INVALIDARG 128
# define ERR_CTRLC 130

/* Lexer */
enum	e_lexeme
{
	INFILE = 1,
	OUTFILE,
	HEREDOC,
	APPEND,
	PIPE,
	BUILTIN,
	CMD,
	ARG
};

typedef struct s_heredoc
{
	int		*fd;
}			t_heredoc;

typedef struct s_exec
{
	char			**cmd;
	int				lex;
	int				fd_in;
	int				fd_out;
}			t_exec;

typedef struct t_args
{
	int		index;
	int		pipis[2];
	int		pipes[2];
}			t_args;

typedef struct s_data
{
	char	*prompt;
	char	*home;
	t_list	*env;
	t_list	*token;
	int		*lexer;
	t_exec	*exec;
	int		has_cmd;
	int		has_builtin;
	int		process_count;
	int		builtin_check;
	t_args	*args;
	int		exit_status;
	int		*fd_heredoc;
}			t_data;

/* Init */
void	copy_env(t_list **list, char **env, t_data *data);
void	init_readline(t_data *data);

/* Signal */
void	sigint_parent_process(int signal);
void	signal_ignore(void);
void	signal_default(void);
void	sigint_heredoc(int signal);
int		*get_heredoc_flag(void);

/* Token and syntax*/
int		tokenization(t_data *data);
int		lex_analysis(t_data *data);
int		syntax_analysis(int *lexer, int len);
int		is_quoted(char c, int identifier);
int		is_redirect(int value);

/* Fix input */
int		check_for_quotes(t_data *data);
void	check_var(t_data *data);
char	*expand_exit_status(char *str, int index, int exit_status);
char	*search_and_expand_var(char *str, t_data *data);
char	*expand_utils(t_data *data, char *str, int i);
void	check_tildes(t_list *token, char *home);
char	*search_and_remove_quotes(char *str);
char	*check_heredoc_var(char *str, t_data *data);
char	*get_key(char *str, int start, int end);
char	*check_var_heredoc(char *str, t_data *data);

/* Exec */
void	execute(t_data *data);
void	child_process(t_data *data, t_list *token, int *lexer, pid_t *pids);
void	deal_with_pipes(t_data *data);
void	get_cmd_and_args(t_list *token, int *lexer, t_data *data);
void	finally_execute(t_data *data, int fd[], pid_t *pids);
void	close_pipes(t_args *args);
void	recycle_pipe(t_args *args);
void	execute_builtin(t_data *data, t_exec *exec, pid_t *pids);
void	wait_all_processes(t_data *data, pid_t *pids, int flag);

/* Builtin */
void	exit_builtin(t_data *data, pid_t *pids, char **args);
void	env_builtin(t_data *data, char **args);
void	pwd_builtin(t_data *data);
void	unset_builtin(t_data *data, char **args);
void	export_builtin(t_data *data, char **args);
char	**split_key_and_value(char *str, char c);
int		check_key(char *str);
void	print_export(t_list *export);
void	echo_builtin(t_data *data, char **args);
void	cd_builtin(t_data *data, char **args);

/* Redirect */
int		validate_files(t_list *token, int *lexer, int *fd_in, int *fd_out);
void	redirect_files(int fd_in, int fd_out);
void	close_files(int fd_in, int fd_out);
int		check_heredoc(t_data *data);
void	delete_heredoc_files(t_data *data);

/* Free */
void	free_cmd_not_found(char **path, char **env, t_data *data, pid_t *pids);
void	free_builtin(t_data *data, pid_t *pids);
void	free_for_all(t_data *data);
void	free_list(t_list *list);
void	free_exec(t_exec *exec);

#endif